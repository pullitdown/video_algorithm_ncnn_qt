#include "my_widget.h"



// class my_widget:public: QMainWindow
// {
//     Q_OBJECT

// public:
//     my_widget(QWidget *parent=Q_BULLPTR);
// private slots:
//     void on_open_camera_bt_clicked();
// private:
//   UI::Ui_main_widget *ui;
// }


/***
 * QWidget *verticalLayoutWidget;
    QVBoxLayout *img_layout;
    QLabel *first_img;
    QLabel *second_img;
    QWidget *verticalLayoutWidget_2;
    QVBoxLayout *button_layout;
    QToolButton *open_camera_bt;
    QToolButton *face_detectiom_bt;
    QToolButton *background_blurring_bt;
    QToolButton *camera_stabilization_bt;
    QToolButton *facial_beautification_bt;
    QListView *data_view;
 * ***/

my_widget::my_widget(QWidget *parent):QMainWindow(parent){
    this->ui=new Ui::main_widget();
    this->time_count=new QTime();
    this->img_path="/home/stepf/world/img/R.png";
    this->path="/home/stepf/world/video_algorithm_ncnn_qt/param/";
    this->use_unet=1;
    this->use_yolact=0;

    if (this->yolov5.load_param(&(path+"yolov5s.ncnn.param")[0]))
        exit(-1);
    if (this->yolov5.load_model(&(path+"yolov5s.ncnn.bin")[0]))
        exit(-1);
    this->yolact.opt.use_vulkan_compute = true;
    if (this->yolact.load_param("/home/stepf/world/video_algorithm_ncnn_qt/param/yolact.param"))
        exit(-1);
    if (this->yolact.load_model("/home/stepf/world/video_algorithm_ncnn_qt/param/yolact.bin"))
        exit(-1);
    this->unet.opt.use_vulkan_compute = true;
    if (this->unet.load_param("/home/stepf/world/video_algorithm_ncnn_qt/param/unet.ncnn.param"))
        exit(-1);
    if (this->unet.load_model("/home/stepf/world/video_algorithm_ncnn_qt/param/unet.ncnn.bin"))
        exit(-1);
    ui->setupUi(this);
    this->camera_is_open=0;
    this->ms=10;
    this->func_num=5;
    this->background_img=cv::imread(img_path,3);
    for(int i=0;i<this->func_num;i++)this->tiktok[i]=new QTimer(this);
    connect(this->tiktok[0], SIGNAL(timeout()), this, SLOT(capPicture()));
    connect(this->ui->open_camera_bt,SIGNAL(clicked()),this,SLOT(on_open_camera_bt_clicked()));
    connect(this->tiktok[1], SIGNAL(timeout()), this, SLOT(capDetect()));
    connect(this->ui->face_detectiom_bt,SIGNAL(clicked()),SLOT(on_face_detectiom_bt_clicked()));
    connect(this->tiktok[2], SIGNAL(timeout()), this, SLOT(capBlur()));
    connect(this->ui->background_blurring_bt,SIGNAL(clicked()),SLOT(on_background_blurring_bt_clicked()));
    // connect(this->ui->camera_stabilization_bt,SIGNAL(clicked),SLOT(on_camera_stabilization_bt_clicked));
    // connect(this->ui->facial_beautification_bt,SIGNAL(clicked),SLOT(on_facial_beautification_bt_clicked));
}


void my_widget::capBlur(){
    if(this->camera_is_open==0)this->tiktok[2]->stop();
#if VANQ_USE_UVC
        this->cap.read(this->current_img);
#endif
#if VANQ_USE_ASTRA
        read_astra();
#endif
    std::vector<Object_yolact> objs;
    
    time_count->start();
    this->operate_img=this->current_img.clone();//memory leak
    if(this->use_yolact)
    {
        detect_yolact(this->yolact,this->current_img,objs);
        draw_objects(this->operate_img,objs);
    }
    else if (this->use_unet)
    {
        detect_unet(this->unet,this->operate_img,this->background_img,0.3,1);
    }
    this->ms=time_count->elapsed();
    qobject_cast<QLabel *>(this->ui->img_layout->itemAt(0)->widget())->setPixmap
         (QPixmap::fromImage(Mat2Image(this->current_img)));
    qobject_cast<QLabel *>(this->ui->img_layout->itemAt(1)->widget())->setPixmap
         (QPixmap::fromImage(Mat2Image(this->operate_img))); 
    this->ui->fps_lb->setText("fps:"+QString::number(1000/this->ms));
    this->ui->opms_lb->setText("op_ms:"+QString::number(this->ms));
    this->ui->opname_lb->setText("op_name: backgroud blur");
}


void my_widget::capDetect(){
    if(this->camera_is_open==0)this->tiktok[1]->stop();
#if VANQ_USE_UVC
        this->cap.read(this->current_img);
#endif
#if VANQ_USE_ASTRA
        read_astra();
#endif
    std::vector<Object_yolov5s> objs;
    
    time_count->start();
    detect_yolov5(this->yolov5,this->current_img,objs);
    this->operate_img=this->current_img.clone();//memory leak
    draw_objects(this->operate_img,objs);
    this->ms=time_count->elapsed();
    qobject_cast<QLabel *>(this->ui->img_layout->itemAt(0)->widget())->setPixmap
         (QPixmap::fromImage(Mat2Image(this->current_img)));
    qobject_cast<QLabel *>(this->ui->img_layout->itemAt(1)->widget())->setPixmap
         (QPixmap::fromImage(Mat2Image(this->operate_img))); 
    this->ui->fps_lb->setText("fps:"+QString::number(1000/this->ms));
    this->ui->opms_lb->setText("op_ms:"+QString::number(this->ms));
    this->ui->opname_lb->setText("op_name: detect face");
}


void my_widget::on_background_blurring_bt_clicked(){

    /***
     * 1.click the botton, compute the time detect algorithm need and start a qtimer
     * 2.set the bt text to close detect  op name
     * 3.show the op run time  , fps equels
     * 4.click again to close the op
     * ***/

    if(this->camera_is_open==1)
    {
        
        for(int i=0;i<this->func_num;i++)if(this->tiktok[i]->isActive())this->tiktok[i]->stop();
        QTimer::singleShot(10, this,SLOT(capBlur()));
        
        this->tiktok[2]->start(this->ms);
    }
    else{
        //QMessageBox::information(this,tr("warming"),tr("camera close , detect faild."));
    }
    
}

void my_widget::on_face_detectiom_bt_clicked(){

    /***
     * 1.click the botton, compute the time detect algorithm need and start a qtimer
     * 2.set the bt text to close detect  op name
     * 3.show the op run time  , fps equels
     * 4.click again to close the op
     * ***/

    if(this->camera_is_open==1)
    {
        std::cout<<"wtf"<<std::endl;
        for(int i=0;i<this->func_num;i++)if(this->tiktok[i]->isActive())this->tiktok[i]->stop();
        QTimer::singleShot(10, this,SLOT(capDetect()));
        
        this->tiktok[1]->start(this->ms);
    }
    else{
        //QMessageBox::information(this,tr("warming"),tr("camera close , detect faild."));
    }
    
}

void my_widget::capPicture(){
    
    if(this->camera_is_open==1){
#if VANQ_USE_UVC
        this->cap.read(this->current_img);
#endif
#if VANQ_USE_ASTRA
        read_astra();
#endif
        qobject_cast<QLabel *>(this->ui->img_layout->itemAt(0)->widget())->setPixmap
        (QPixmap::fromImage(Mat2Image(this->current_img)));
        
        this->ui->fps_lb->setText("fps:"+QString::number(1000/this->ms));
        this->ui->opms_lb->setText("op_ms:0");
        this->ui->opname_lb->setText("op_name: none");
    }   
}
        


void my_widget::on_open_camera_bt_clicked()
{
    
    if(this->camera_is_open==0)
    {
        this->camera_is_open=1;
        qobject_cast<QToolButton *>(ui->button_layout->itemAt(0)->widget())->setText("close camera");

#if VANQ_USE_UVC
        this->cap.open(0,cv::CAP_V4L2 );
        int fps = cap.get(cv::CAP_PROP_FPS);
        if(!cap.isOpened()) {
            std::cout<<"cannot open camera"<<std::endl;
            return;
        }
#endif

#if VANQ_USE_ASTRA
        this->cap_astra.my_astra_init();
        
#endif
        this->tiktok[0]->start(this->ms);
    }
    else{
        
#if VANQ_USE_UVC
        this->cap.release();
#endif

#if VANQ_USE_ASTRA
        this->cap_astra.my_astra_terminate();
#endif
        this->tiktok[0]->stop();
        qobject_cast<QLabel *>(this->ui->img_layout->itemAt(0)->widget())->setText("video closed");
        qobject_cast<QToolButton *>(this->ui->button_layout->itemAt(0)->widget())->setText("open camera");
        this->camera_is_open=0; 
    }
}



QImage my_widget::Mat2Image(cv::Mat inmat)
{
   cv::Mat mat = inmat.clone();
   // 8-bits unsigned, NO. OF CHANNELS=1  8位无符号单通道
       if(mat.type()==CV_8UC1)
       {
           // Set the color table (used to translate colour indexes to qRgb values)
           //设置颜色表（用于将颜色索引转换为qRgb值）
           QVector<QRgb> colorTable;
           for (int i=0; i<256; i++)
               colorTable.push_back(qRgb(i,i,i));
           // Copy input Mat 复制输入 Mat
           const uchar *qImageBuffer = (const uchar*)mat.data;
           // Create QImage with same dimensions as input Mat
           //创建与输入Mat相同尺寸的QImage
           QImage img(qImageBuffer, mat.cols, mat.rows, mat.step, QImage::Format_Indexed8);
           img.setColorTable(colorTable);
           return img;
       }
       // 8-bits unsigned, NO. OF CHANNELS=3 8位无符号3通道
       else if(mat.type()==CV_8UC3)
       {
           // Copy input Mat  复制输入 Mat
           const uchar *qImageBuffer = (const uchar*)mat.data;
           // Create QImage with same dimensions as input Mat
           //创建与输入Mat相同尺寸的QImage
           QImage img(qImageBuffer, mat.cols, mat.rows, mat.step, QImage::Format_RGB888);
           return img.rgbSwapped();
       }
       else if(mat.type() == CV_8UC4) //8位无符号4通道
       {
           // Copy input Mat
           const uchar *pSrc = (const uchar*)mat.data;
           // Create QImage with same dimensions as input Mat
           QImage image(pSrc, mat.cols, mat.rows, mat.step, QImage::Format_ARGB32);
           return image.copy();
       }
       else
       {
           qDebug() << "ERROR: Mat could not be converted to QImage.";
           return QImage();
       }
}
// //QImage转Mat
// cv::Mat my_widget::Image2Mat(QImage image)
// {
//    cv::Mat mat;
//    switch(image.format())
//    {
//        case QImage::Format_ARGB32:
//        case QImage::Format_RGB32:
//        case QImage::Format_ARGB32_Premultiplied:
//            mat = Mat(image.height(), image.width(), CV_8UC4, (void*)image.constBits(), image.bytesPerLine());
//            break;
//        case QImage::Format_RGB888:
//            mat = Mat(image.height(), image.width(), CV_8UC3, (void*)image.constBits(), image.bytesPerLine());
//            cv::cvtColor(mat, mat, cv::COLOR_YUV2RGB_NV12);    //CV_BGR2RGB
//            break;
//        case QImage::Format_Indexed8:
//            mat = Mat(image.height(), image.width(), CV_8UC1, (void*)image.constBits(), image.bytesPerLine());
//            break;
//        default:
//            break;
//    }
//    return mat;
// }

