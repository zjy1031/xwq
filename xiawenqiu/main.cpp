#include "mainwindow.h"
#include "chart.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
//    Chart b;
//    b.show();

    return a.exec();
}
