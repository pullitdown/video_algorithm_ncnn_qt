#include <QApplication>
#include <QDebug>
#include "my_widget.h"
int main(int argc, char **argv) {
    QApplication a(argc, argv);    //main GUI window
    my_widget mw;
    mw.show();
    return a.exec();
}
