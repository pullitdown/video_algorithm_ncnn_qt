#include <QApplication>
#include <QDebug>
#include "mainwindow.h"
int main(int argc, char **argv) {
    QApplication app(argc, argv);
    MainWindow m;
    m.show();
    qDebug() << "hello vs qt";
    return app.exec();
}
