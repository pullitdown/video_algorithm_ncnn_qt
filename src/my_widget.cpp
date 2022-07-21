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
    this->tiktok=new QTimer(this);
    ui->setupUi(this);
    this->camera_is_open=0;


    connect(this->tiktok, SIGNAL(timeout()), this, SLOT(capPicture()));
    connect(this->ui->open_camera_bt,SIGNAL(clicked),this,SLOT(on_open_camera_bt_clicked));
    // connect(this->ui->face_detectiom_bt,SIGNAL(clicked),SLOT(on_face_detectiom_bt_clicked));
    // connect(this->ui->background_blurring_bt,SIGNAL(clicked),SLOT(on_background_blurring_bt_clicked));
    // connect(this->ui->camera_stabilization_bt,SIGNAL(clicked),SLOT(on_camera_stabilization_bt_clicked));
    // connect(this->ui->facial_beautification_bt,SIGNAL(clicked),SLOT(on_facial_beautification_bt_clicked));
}


void my_widget::capPicture(){
    if(this->camera_is_open==1){
        this->cap.read(this->current_img);
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
        //  camera->start();//启动摄像头
        this->cap.open(0);
        int fps = cap.get(cv::CAP_PROP_FPS);
        if(!cap.isOpened()) {
            std::cout<<"cannot open camera"<<std::endl;
            return;
        }
        this->ms=10;
        this->tiktok->start(this->ms);
        std::cout<<this->tiktok->isActive()<<" "<<this->tiktok->remainingTime()<<std::endl;
    }
    else{
        this->tiktok->stop();
        this->cap.release();
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

