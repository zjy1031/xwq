#ifndef CHART_H
#define CHART_H

#include <QWidget>
#include <QChart>        //图表类(模型)
#include <QChartView>    //图表视图类
#include <QValueAxis>    //坐标轴(值)
#include <QDateTimeAxis> //时间轴
#include <QSplineSeries> //平滑曲线效果
#include <QLineSeries>   //折线效果
#include <QDateTime>     //日期时间
#include <QHBoxLayout>
#include <QJsonArray>
#include <QJsonObject>
#include <QMouseEvent>
#include <QPainter>
#include <QPaintEvent>
using namespace QtCharts;

class Chart : public QWidget
{
    Q_OBJECT

public:
    Chart(QWidget *parent = nullptr);
    ~Chart();
    void  initChart(); //初始化属性
    void  setXYTitle(QString XTitle,QString YTitle);//设置坐标轴 标题
    void  setXRange(int Xmin,int Xmax);//设置X坐标轴取值范围
    void  setYRange(int Ymin,int Ymax);//设置Y坐标取值范围
    void  setShowData(const QJsonArray& array);//图表数据设置
    void  setShowData2(const QJsonObject& json);//图表数据设置
    void  setXShowFormat(int flag);//设置X轴(时间)显示格式
    void  setShowFlag(bool flag=true);//设置曲线显示或折线显示，默认曲线
    void  testFun();//测试代码
    void  testFun2();//测试2
protected:

public slots:

private:
    QChart   *chart;         //图表
    QChartView  *chartView;  //图表视图,用来显示图表
    QDateTimeAxis    *timeAxis; //时间轴
    QValueAxis       *axisY;//Y坐标轴
    QSplineSeries    *spline;//曲线效果
    QLineSeries      *line;//折线效果
    QHBoxLayout      *hLayout;
    bool     showFlag;//曲线显示/折线显示 (true/false)
};

#endif // CHART_H
