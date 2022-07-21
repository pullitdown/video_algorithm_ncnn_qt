#ifndef MAIN_WIDGET_H
#define MAIN_WIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_main_widget
{
public:
    QWidget *verticalLayoutWidget;
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
    QWidget *verticalLayoutWidget_3;
    QVBoxLayout *verticalLayout;
    QLabel *fps_lb;
    QLabel *opms_lb;
    QLabel *opname_lb;

    void setupUi(QWidget *main_widget)
    {
        if (main_widget->objectName().isEmpty())
            main_widget->setObjectName(QString::fromUtf8("main_widget"));
        main_widget->resize(735, 896);
        verticalLayoutWidget = new QWidget(main_widget);
        verticalLayoutWidget->setObjectName(QString::fromUtf8("verticalLayoutWidget"));
        verticalLayoutWidget->setGeometry(QRect(19, 19, 521, 861));
        img_layout = new QVBoxLayout(verticalLayoutWidget);
        img_layout->setObjectName(QString::fromUtf8("img_layout"));
        img_layout->setContentsMargins(0, 0, 0, 0);
        first_img = new QLabel(verticalLayoutWidget);
        first_img->setObjectName(QString::fromUtf8("first_img"));

        img_layout->addWidget(first_img);

        second_img = new QLabel(verticalLayoutWidget);
        second_img->setObjectName(QString::fromUtf8("second_img"));

        img_layout->addWidget(second_img);

        verticalLayoutWidget_2 = new QWidget(main_widget);
        verticalLayoutWidget_2->setObjectName(QString::fromUtf8("verticalLayoutWidget_2"));
        verticalLayoutWidget_2->setGeometry(QRect(560, 20, 161, 361));
        button_layout = new QVBoxLayout(verticalLayoutWidget_2);
        button_layout->setObjectName(QString::fromUtf8("button_layout"));
        button_layout->setContentsMargins(0, 0, 0, 0);
        open_camera_bt = new QToolButton(verticalLayoutWidget_2);
        open_camera_bt->setObjectName(QString::fromUtf8("open_camera_bt"));

        button_layout->addWidget(open_camera_bt);

        face_detectiom_bt = new QToolButton(verticalLayoutWidget_2);
        face_detectiom_bt->setObjectName(QString::fromUtf8("face_detectiom_bt"));

        button_layout->addWidget(face_detectiom_bt);

        background_blurring_bt = new QToolButton(verticalLayoutWidget_2);
        background_blurring_bt->setObjectName(QString::fromUtf8("background_blurring_bt"));

        button_layout->addWidget(background_blurring_bt);

        camera_stabilization_bt = new QToolButton(verticalLayoutWidget_2);
        camera_stabilization_bt->setObjectName(QString::fromUtf8("camera_stabilization_bt"));

        button_layout->addWidget(camera_stabilization_bt);

        facial_beautification_bt = new QToolButton(verticalLayoutWidget_2);
        facial_beautification_bt->setObjectName(QString::fromUtf8("facial_beautification_bt"));

        button_layout->addWidget(facial_beautification_bt);

        verticalLayoutWidget_3 = new QWidget(main_widget);
        verticalLayoutWidget_3->setObjectName(QString::fromUtf8("verticalLayoutWidget_3"));
        verticalLayoutWidget_3->setGeometry(QRect(560, 630, 161, 251));
        verticalLayout = new QVBoxLayout(verticalLayoutWidget_3);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        fps_lb = new QLabel(verticalLayoutWidget_3);
        fps_lb->setObjectName(QString::fromUtf8("fps_lb"));

        verticalLayout->addWidget(fps_lb);

        opms_lb = new QLabel(verticalLayoutWidget_3);
        opms_lb->setObjectName(QString::fromUtf8("opms_lb"));

        verticalLayout->addWidget(opms_lb);

        opname_lb = new QLabel(verticalLayoutWidget_3);
        opname_lb->setObjectName(QString::fromUtf8("opname_lb"));

        verticalLayout->addWidget(opname_lb);

        verticalLayoutWidget->raise();
        verticalLayoutWidget_2->raise();
        verticalLayoutWidget_3->raise();
        opname_lb->raise();

        retranslateUi(main_widget);

        QMetaObject::connectSlotsByName(main_widget);
    } // setupUi

    void retranslateUi(QWidget *main_widget)
    {
        main_widget->setWindowTitle(QApplication::translate("main_widget", "Form", nullptr));
        first_img->setText(QApplication::translate("main_widget", "video closed", nullptr));
        second_img->setText(QApplication::translate("main_widget", "video closed", nullptr));
        open_camera_bt->setText(QApplication::translate("main_widget", "open camera", nullptr));
        face_detectiom_bt->setText(QApplication::translate("main_widget", "face detection", nullptr));
        background_blurring_bt->setText(QApplication::translate("main_widget", "background blurring", nullptr));
        camera_stabilization_bt->setText(QApplication::translate("main_widget", "camera stabilization", nullptr));
        facial_beautification_bt->setText(QApplication::translate("main_widget", "facial beautification", nullptr));
        fps_lb->setText(QApplication::translate("main_widget", "fps:", nullptr));
        opms_lb->setText(QApplication::translate("main_widget", "op_ms:", nullptr));
        opname_lb->setText(QApplication::translate("main_widget", "op_name:", nullptr));
    } // retranslateUi

};

namespace Ui {
    class main_widget: public Ui_main_widget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // MAIN_WIDGET_H