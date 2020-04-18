#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->resize(1300,768);
    hum1 = 0;
    tmp1 = 0;
    //修改名称
    this->setWindowTitle("夏雯秋的上位机");
    //修改图标
    this->setWindowIcon(QIcon(":/icons/ooopic.ico"));

    QPixmap pixmap = QPixmap(":/icons/a1.jpg").scaled(this->size());
    QPalette  palette (this->palette());
    palette .setBrush(QPalette::Background, QBrush(pixmap));
    this-> setPalette( palette );

    ui->label->setFont(QFont("幼圆",12,75));
    ui->label_2->setFont(QFont("幼圆",12,75));
    ui->label_3->setFont(QFont("幼圆",12,75));
    ui->label->setText(QDateTime::currentDateTime().toString("yyyy-MM-dd  dddd  hh:mm:ss "));
    timer=new QTimer;
    connect(timer,SIGNAL(timeout()),this,SLOT(timerSlot()));
    timer->start(1000);

    //子界面
    stack=new QStackedWidget(this);
    stack->setGeometry(350,250,900,500);
    widget1=new TempChart;
    widget2=new HumChart;
    stack->addWidget(widget1);
    stack->addWidget(widget2);

    //检测串口
    serial = new QSerialPort;//构造串口对象
    foreach(const QSerialPortInfo &info, QSerialPortInfo::availablePorts())
        {
            qDebug() << "Name        : " << info.portName();
            qDebug() << "Description : " << info.description();
            qDebug() << "Manufacturer: " << info.manufacturer();
            if (ui->duankou_2->currentText() != info.portName())
                ui->duankou_2->addItem(info.portName());
        }

    connect(serial,SIGNAL(readyRead()),this,SLOT(readSlot()));

    //仪表盘
    tempshow=new ShowData(this);
    tempshow->setGeometry(525,50,200,200);
    tempshow->setMaxAndMin(80,-20);
    tempshow->setName("温度","℃");
    tempshow->setFixedSize(200,200);

    humshow=new ShowData(this);
    humshow->setGeometry(800,50,200,200);
    humshow->setMaxAndMin(100,0);
    humshow->setName("湿度","%");
    humshow->setFixedSize(200,200);

    stack->setCurrentIndex(0);
}

MainWindow::~MainWindow()
{
    delete ui;
}

//初始化串口
void MainWindow::initSerialPort()
{
    serial->setPortName(ui->duankou_2->currentText());//选取串口
    serial->setBaudRate(ui->botelv_2->currentText().toInt());//设置波特率
    if(ui->databit_2->currentText() == 8)
    {
        serial->setDataBits(QSerialPort::Data8);//设置数据位
    }else if(ui->databit_2->currentText() == 7)
    {
        serial->setDataBits(QSerialPort::Data7);
    }
    else if(ui->databit_2->currentText() == 6)
    {
        serial->setDataBits(QSerialPort::Data6);
    }
    else if(ui->databit_2->currentText() == 5)
    {
        serial->setDataBits(QSerialPort::Data5);
    }

    serial->setParity(QSerialPort::NoParity);//设置校验
    serial->setFlowControl(QSerialPort::NoFlowControl);//设置流控制
    serial->setStopBits(QSerialPort::OneStop);//设置停止位
}

//打开串口
void MainWindow::on_pushButton_clicked()
{
    initSerialPort();
    if(serial->open(QIODevice::ReadWrite))
    {
        qDebug()<<"打开串口成功！";
        ui->textBrowser->append("打开串口成功！");
    }else{
        qDebug()<<"打开串口失败！";
        ui->textBrowser->append("打开串口失败！");
    }
}

//关闭串口
void MainWindow::on_pushButton_2_clicked()
{
    serial->close();
    qDebug()<<"串口已关闭！";
    ui->textBrowser->append("串口已关闭！");
}

void MainWindow::readSlot()
{
    if(!serial)
        return ;
    QByteArray data;
    if(serial->bytesAvailable())
    {
        data.append(serial->readAll());
    }
    if(data.size()<14)
        return;
//    qDebug()<<data.toHex()<<data.toHex()[0]<<data.toHex()[1]<<data.toHex()[13];
    ui->textBrowser->append("原始帧:"+data.toHex());
    QByteArray hum,tmp;
    hum[0] = data[7];
    hum[1] = data[8];
    tmp[0] = data[9];
    tmp[1] = data[10];
    hum1 = hum.toHex().toInt(nullptr,16)/10.0;
    tmp1 = tmp.toHex().toInt(nullptr,16)/10.0;
    qDebug()<<hum1;
    qDebug()<<tmp1;
    ui->textBrowser->append("湿度为:"+QString::number(hum1));
    ui->textBrowser->append("温度为:"+QString::number(tmp1));
    ui->label_2->setText("温度为:"+QString::number(tmp1)+"℃");
    ui->label_3->setText("湿度为:"+QString::number(hum1)+"%");
    //数据换算
    //
    //
    tempshow->setData(tmp1);
    humshow->setData(hum1);
    json_hum.insert(QString::number(QDateTime::currentSecsSinceEpoch()),hum1);
    json_tmp.insert(QString::number(QDateTime::currentSecsSinceEpoch()),tmp1);
    widget1->tempchart->setShowData2(json_tmp);
    widget2->humchart->setShowData2(json_hum);
}

//清空textbrowser
void MainWindow::on_pushButton_3_clicked()
{
    ui->textBrowser->clear();
}


//切换湿度图表
void MainWindow::on_pushButton_5_clicked()
{
    stack->setCurrentIndex(1);
}

//切换温度图表
void MainWindow::on_pushButton_4_clicked()
{
    stack->setCurrentIndex(0);
}

void MainWindow::timerSlot()
{
    ui->label->setText(QDateTime::currentDateTime().toString("yyyy-MM-dd dddd hh:mm:ss "));
}

