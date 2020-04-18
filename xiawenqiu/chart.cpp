#include "chart.h"
#include <QDebug>
#include <QSizeF>
Chart::Chart(QWidget *parent)
    : QWidget(parent),showFlag(true)
{
    this->resize(1024,768);
//    initChart();
//    testFun();

}

Chart::~Chart()
{
    delete hLayout;delete spline;delete chart;
    delete chartView;delete axisY;delete timeAxis;
    delete line;
}

void Chart::initChart()
{
    //曲线效果
    spline = new QSplineSeries;
    //折线效果
    line = new QLineSeries;
    //图表和视图
    chart = new QChart;
    chart->legend()->hide(); //隐藏图例
//    line->setName("test");
//    chart->legend()->setFont(QFont("黑体",15));
    chart->setAnimationOptions(QChart::SeriesAnimations);//设置曲线呈动画效果显示
    chartView = new QChartView(chart,this);
    chartView->resize(this->width(),this->height());
    chartView->setRenderHint(QPainter::Antialiasing);//抗锯齿
    //构建坐标轴
    axisY = new QValueAxis;       //Y轴，显示数值
    axisY->setLabelFormat("%.2f");//设置刻度的格式
    axisY->setGridLineVisible(true);//设置网格线可见
    axisY->setLabelsFont(QFont("黑体",15));//设置轴字体
    axisY->setTickCount(11); //设置分割线数
    axisY->setMinorTickCount(2);//设置每格刻度线数目

    timeAxis = new QDateTimeAxis; //X轴，时间轴
    timeAxis->setTitleText("时间");//X轴标题
    timeAxis->setLabelsFont(QFont("黑体",15));//设置轴字体
    timeAxis->setTickCount(6); //设置分割线数

    //布局
    hLayout = new QHBoxLayout;
    hLayout->addWidget(chartView);
    this->setLayout(hLayout);
}
//设置坐标轴标题
void Chart::setXYTitle(QString XTitle, QString YTitle)
{
    timeAxis->setTitleText(YTitle);
    axisY->setTitleText(XTitle);
}
//设置X坐标轴取值范围(时间)
void Chart::setXRange(int Xmin, int Xmax)
{
    timeAxis->setRange(QDateTime::fromTime_t(Xmin),QDateTime::fromTime_t(Xmax));
}
//设置Y坐标轴取值范围
void Chart::setYRange(int Ymin, int Ymax)
{
    axisY->setRange(Ymin,Ymax);
}
//将jsonarray中的数据显示到图表中
void Chart::setShowData(const QJsonArray &array)
{
    //首先去除之前的属性
    chart->removeSeries(spline);
    chart->removeSeries(line);
    spline->clear();
    line->clear();
    //循环获取数据
    for(int i=0;i<array.size();++i)
    {
        if(showFlag)
            spline->append(i,array.at(i).toDouble()); //将数据以曲线方式显示
        else
            line->append(i,array.at(i).toDouble()); //将数据以折线方式显示
    }
    if(showFlag)
    {
        chart->addSeries(spline);//将曲线值添加到chart中
    }else
    {
        chart->addSeries(line);//将折线值添加到chart中
    }
}
//图表数据显示
void Chart::setShowData2(const QJsonObject &json)
{
    //首先去除旧的属性
    chart->removeSeries(spline);
    chart->removeSeries(line);
    spline->clear();
    line->clear();
    //提取数据
    QJsonObject::const_iterator  it;
    int  i = 0;
    for(it=json.begin();it!=json.end();it++)
    {
        double value = it.value().toDouble();
        if(showFlag)
            spline->append(i,value);
        else
            line->append(i,value);
        i++;
    }
    setXRange(json.begin().key().toInt(),
              (json.end()-1).key().toInt());
    //将 spline/line添加到 chart
    if(showFlag)
    {
        chart->addSeries(spline);
    }else
    {
        chart->addSeries(line);
    }
    //添加坐标轴到 chart
    chart->setAxisY(axisY,spline);
    chart->addAxis(timeAxis,Qt::AlignBottom);
}
//设置X轴(时间)显示格式
void Chart::setXShowFormat(int flag)
{
    switch (flag) {
    case 0:
        timeAxis->setFormat("hh:mm:ss");
        break;
    case 1:
        timeAxis->setFormat("hh:mm");
        break;
    case 2:
        timeAxis->setFormat("dd日hh时");
        break;
    case 3:
        timeAxis->setFormat("MM月dd日hh时");
        break;
    case 4:
        timeAxis->setFormat("MM月dd日");
        break;
    case 5:
        timeAxis->setFormat("yy年MM月dd日");
        break;
    case 6:
        timeAxis->setFormat("yyyy年MM月dd日");
        break;
    default:
        break;
    }
}

void Chart::setShowFlag(bool flag)
{
    this->showFlag = flag;
}
//测试代码
void Chart::testFun()
{
    //...
    QJsonObject json;
    json.insert(QString::number(QDateTime::currentSecsSinceEpoch()-3600),45);
    json.insert(QString::number(QDateTime::currentSecsSinceEpoch()-3400),45);
    json.insert(QString::number(QDateTime::currentSecsSinceEpoch()-3200),35);
    json.insert(QString::number(QDateTime::currentSecsSinceEpoch()-3000),45);
    json.insert(QString::number(QDateTime::currentSecsSinceEpoch()-2800),55);
    json.insert(QString::number(QDateTime::currentSecsSinceEpoch()-2600),45);
    json.insert(QString::number(QDateTime::currentSecsSinceEpoch()-2400),60);
    json.insert(QString::number(QDateTime::currentSecsSinceEpoch()-2200),45);
    json.insert(QString::number(QDateTime::currentSecsSinceEpoch()-2000),65);
    json.insert(QString::number(QDateTime::currentSecsSinceEpoch()-1800),45);
    json.insert(QString::number(QDateTime::currentSecsSinceEpoch()-1600),55);
    json.insert(QString::number(QDateTime::currentSecsSinceEpoch()-1400),45);
    json.insert(QString::number(QDateTime::currentSecsSinceEpoch()-1200),39);
    json.insert(QString::number(QDateTime::currentSecsSinceEpoch()-1000),45);
    json.insert(QString::number(QDateTime::currentSecsSinceEpoch()-800),45);
    json.insert(QString::number(QDateTime::currentSecsSinceEpoch()-600),45);
    json.insert(QString::number(QDateTime::currentSecsSinceEpoch()-400),57);
    json.insert(QString::number(QDateTime::currentSecsSinceEpoch()-200),45);
    json.insert(QString::number(QDateTime::currentSecsSinceEpoch()),39);

    setXYTitle("湿度(%)","时间");
    setYRange(0,100);
    setXShowFormat(0);
    setShowFlag();
    setShowData2(json);
}

//测试代码
void Chart::testFun2()
{
    //...
    QJsonObject json;
    json.insert(QString::number(QDateTime::currentSecsSinceEpoch()-3600),19);
    json.insert(QString::number(QDateTime::currentSecsSinceEpoch()-3400),20);
    json.insert(QString::number(QDateTime::currentSecsSinceEpoch()-3200),25);
    json.insert(QString::number(QDateTime::currentSecsSinceEpoch()-3000),45);
    json.insert(QString::number(QDateTime::currentSecsSinceEpoch()-2800),15);
    json.insert(QString::number(QDateTime::currentSecsSinceEpoch()-2600),20);
    json.insert(QString::number(QDateTime::currentSecsSinceEpoch()-2400),28);
    json.insert(QString::number(QDateTime::currentSecsSinceEpoch()-2200),30);
    json.insert(QString::number(QDateTime::currentSecsSinceEpoch()-2000),28);
    json.insert(QString::number(QDateTime::currentSecsSinceEpoch()-1800),25);
    json.insert(QString::number(QDateTime::currentSecsSinceEpoch()-1600),25);
    json.insert(QString::number(QDateTime::currentSecsSinceEpoch()-1400),25);
    json.insert(QString::number(QDateTime::currentSecsSinceEpoch()-1200),24);
    json.insert(QString::number(QDateTime::currentSecsSinceEpoch()-1000),26);
    json.insert(QString::number(QDateTime::currentSecsSinceEpoch()-800),27);
    json.insert(QString::number(QDateTime::currentSecsSinceEpoch()-600),25);
    json.insert(QString::number(QDateTime::currentSecsSinceEpoch()-400),22);
    json.insert(QString::number(QDateTime::currentSecsSinceEpoch()-200),21);
    json.insert(QString::number(QDateTime::currentSecsSinceEpoch()),20);

    setXYTitle("温度(℃)","时间");
    setYRange(0,100);
    setXShowFormat(0);
    setShowFlag();
    setShowData2(json);
}


