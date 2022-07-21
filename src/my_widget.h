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
#include <QDateTime>
#include<QTimer>

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
    //~my_widget(){delete ui;};
    cv::Mat Image2Mat(QImage image);
    QImage Mat2Image(cv::Mat mat);

private slots:
    void on_open_camera_bt_clicked();
    void capPicture();
    // void on_face_detectiom_bt_clicked();
    // void on_background_blurring_bt_clicked();
    // void on_camera_stabilization_bt_clicked();
    // void on_facial_beautification_bt_clicked();
    
private:
    bool camera_is_open;
    Ui::main_widget *ui;
    QTimer *tiktok;
    cv::VideoCapture cap;
    cv::Mat current_img;
    int ms;
    QTimer *time_count;
};