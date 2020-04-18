#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSerialPortInfo>  //串口信息类
#include <QSerialPort>      //串口驱动类
#include <QDebug>
#include "showdata.h"
#include <QPainter>//画家类
#include <QPaintEvent>//绘制事件
#include <QImage>//图片加载器
#include <QHBoxLayout>  // 水平布局管理器类
#include <QVBoxLayout> //垂直布局管理器类
#include <QJsonObject>
#include "chart.h"
#include <QStackedWidget>
#include "tempchart.h"
#include "humchart.h"
#include<QTimer> //日期时间


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void initSerialPort();  //初始化串口

protected:

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();
    void readSlot();
    void on_pushButton_3_clicked();
    void on_pushButton_5_clicked();
    void on_pushButton_4_clicked();
    void timerSlot();

private:
    Ui::MainWindow *ui;
    QSerialPort *serial;
    ShowData *tempshow;
    ShowData *humshow;
    QImage *image;
    double tmp1;
    double hum1;
    QHBoxLayout *h;
    QJsonObject json_tmp,json_hum;
    QStackedWidget *stack;
    TempChart *widget1;
    HumChart *widget2;
    QTimer   *timer;
};

#endif // MAINWINDOW_H
