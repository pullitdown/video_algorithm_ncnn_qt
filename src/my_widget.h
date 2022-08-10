#include "main_widget.h"
#include <QtWidgets/QMainWindow>
#include <iostream>
#include <QMainWindow>
#include <opencv2/videoio.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <QDebug>
#include <unistd.h>
#include <QLabel>
#include<QMessageBox>
#include <QDateTime>
#include<QTimer>
#include<yolov5_pnnx.h>
#include<yolact.h>
#include<unet.h>
#include <layer.h>
#include <net.h>

// #include"option.h"
#define VANQ_USE_ASTRA 1
#define VANQ_USE_UVCSWAPPER 0
#define VANQ_USE_UVC 0


#if VANQ_USE_ASTRA
    #include<astra_cap.h>
#endif


#if VANQ_USE_UVCSWAPPER

#include "OniSampleUtilities.h"
#include "UVC_Swapper.h"
#include "UVCSwapper.h"
#include "OBTypes.h"
#include "ObCommon.h"
#endif

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
class my_widget:public QMainWindow
{
    Q_OBJECT

public:
    explicit my_widget(QWidget *parent=Q_NULLPTR);
    ~my_widget(){delete ui;for(int i=0;i<this->func_num;i++)delete this->tiktok[i];};
    cv::Mat Image2Mat(QImage image);
    QImage Mat2Image(cv::Mat mat);

private slots:
    void on_open_camera_bt_clicked();
    void capPicture();
    
    void on_face_detectiom_bt_clicked();
    void capDetect();
    void on_background_blurring_bt_clicked();
    void capBlur();
    // void on_camera_stabilization_bt_clicked();
    // void capStabily()
    // void on_facial_beautification_bt_clicked();
    // void capBeautify();
private:
    
    Ui::main_widget *ui;


    /***
     * time counter
    ***/
    QTimer* (tiktok)[5];
    int func_num;
    int ms;
    QTime *time_count;

    /*cap */
#if VANQ_USE_UVC
    cv::VideoCapture cap;
    cv::VideoCapture colorStream;
    cv::VideoCapture depthStream;
    
#endif

#if VANQ_USE_ASTRA
    astra::astra_capture cap_astra;
    void read_astra(){
        // if(this->current_img.cols!=480||this->current_img.rows!=640)
        // cv::resize(this->current_img,this->current_img,cv::Size(640,480));
        // uchar * ptr=this->current_img.data;
        uchar* DD=this->cap_astra.my_astra_update();
        std::cout<<DD[0]<<std::endl;
        // memcpy(ptr, DD, 640*480*3);
    }
#endif

#if VANQ_USE_UVCWAPPER

#endif
    bool camera_is_open;
    /*picture*/
    cv::Mat current_img;
    cv::Mat operate_img;
    cv::Mat background_img;

    /*path*/
    std::string path;
    std::string img_path;

    /*net*/
    ncnn::Net yolov5;
    ncnn::Net yolact;
    ncnn::Net unet;
    bool use_yolact;
    bool use_unet;
    

};