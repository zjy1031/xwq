#include "humchart.h"

HumChart::HumChart(QWidget *parent) : QWidget(parent)
{
    humchart=new Chart(this);
    humchart->initChart();
    humchart->testFun();
    humchart->setGeometry(0,0,900,500);
//    humchart->setXYTitle("湿度(%)","时间");
//    humchart->setYRange(0,100);
//    humchart->setXShowFormat(0);
//    humchart->setShowFlag();
}
