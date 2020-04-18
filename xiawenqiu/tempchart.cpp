#include "tempchart.h"


TempChart::TempChart(QWidget *parent) : QWidget(parent)
{
    tempchart=new Chart(this);
    tempchart->initChart();
    tempchart->testFun2();
    tempchart->setGeometry(0,0,900,500);
//    tempchart->setXYTitle("温度(℃)","时间");
//    tempchart->setYRange(-20,80);
//    tempchart->setXShowFormat(0);
//    tempchart->setShowFlag();
}
