#include "showdata.h"

ShowData::ShowData(QWidget *parent) : QWidget(parent),currentValue(0)
{

}

void ShowData::setData(double data)
{
    this->currentValue=data;
    this->update();
}

void ShowData::setMaxAndMin(int max, int min)
{
    this->max=max;
    this->min=min;
}

void ShowData::setName(QString name, QString unit)
{
    this->name=name;
    this->unit=unit;
}

//重绘函数
void ShowData::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QSizeF s(size());
    double h=s.height();
    double w=s.width();
    point[0]=QPointF(w/3.38,0);
    point[1]=QPointF(0,-h/62.8571);
    point[2]=QPointF(0,h/62.8571);
    point2[0]=QPointF(w/4.4,0);
    point2[1]=QPointF(0,-h/146.666);
    point2[2]=QPointF(0,h/146.666);
    QPainter painter(this);//定义画家对象
    painter.setRenderHint(QPainter::Antialiasing);//消除锯齿
    //1.画表边框
    painter.translate(width()/2,height()/2);//坐标偏移到中心
    QLinearGradient *line=new QLinearGradient(-w/2.2,-h/2.2,w/2.2,h/2.2);
    line->setColorAt(0,QColor("black"));
    line->setColorAt(0.5,QColor("gray"));
    line->setColorAt(1,QColor("white"));
    QPen pen;
    pen.setBrush(*line);//设置画刷
    pen.setWidth(w/22);//设置笔的宽度
    painter.setPen(pen);//将笔交给画家
    painter.drawArc(-w/2.2,-h/2.2,w/2.2*2,h/2.2*2,0*16,360*16);//画圆弧
    //2.画表盘背景
    painter.setPen(Qt::NoPen);//去除笔
    pen.setBrush(QBrush(QColor(0,0,0,220)));//设置颜色
    pen.setWidth(w/2.4444);
    painter.setPen(pen);
    painter.drawArc(-w/4.4,-h/4.4,w/2.2,h/2.2,0*16,360*16);
    //3.画中心圆的套环（图层原因先画在指针及中心圆之前）
    painter.setPen(Qt::NoPen);
    pen.setBrush(QBrush(QColor("gray")));
    pen.setWidth(w/55);
    painter.setPen(pen);
    painter.drawArc(-w/19.13,-h/19.13,w/9.565,h/9.565,0,360*16);
    //4.画指针
    //先确定旋转角度
    painter.rotate(135);//旋转函数
    painter.rotate(270/(max-min)*(currentValue-min));//将指针指向当前值
    painter.setPen(Qt::NoPen);
    painter.setBrush(QBrush(QColor("white")));
    painter.drawConvexPolygon(point,3);
    painter.setBrush(QBrush(QColor("gray")));
    painter.drawConvexPolygon(point2,3);
    //5.画中心圆
    pen.setBrush(QBrush(QColor("white")));
    pen.setWidth(w/31.4285);
    painter.setPen(pen);
    painter.drawArc(-w/62.8,-h/62.8,w/31.4,h/31.4,0,360*16);
    //6.画刻度线
    painter.rotate(-135);//消除初始值的135度
    painter.rotate(-270/(max-min)*(currentValue-min));//消除指针造成的旋转
    painter.rotate(45);//将画家旋转到 刻度线的起始角度
    painter.setPen(Qt::NoPen);
    pen.setColor(QColor("white"));
    double number=100;//要显示的刻度线个数
    double angle=270.0/number;//每个刻度的角度
    for(int i=0;i<=number;++i)
    {
        if(i%10==0)
        {
            pen.setWidth(w/220);
            painter.setPen(pen);
            painter.drawLine(0,h/3.14285,0,h/2.8025);
        }
        else{
            if(i%5==0)
            {
                pen.setWidth(w/440);
                painter.setPen(pen);
                painter.drawLine(0,h/3.05,0,h/2.8025);
            }
            else{
                pen.setWidth(w/440);
                painter.setPen(pen);
                painter.drawLine(0,h/2.953,0,h/2.8025);
            }
        }
        painter.rotate(angle);
    }
    //7.画数字
    painter.rotate(90);//让painter角度转到初始位置
    painter.setFont(QFont("Times",w/33.84615,75));//设置字体
    painter.setPen(Qt::NoPen);
    pen.setColor(QColor("white"));
    for(int i=0;i<=number;i++)
    {
        if(i%10==0)//需要画数字
        {
           painter.setPen(pen);
           painter.rotate(180);
           painter.drawText(-w/22,-h/2.588,QString::number((max-min)/100*i+min));
           painter.rotate(-180);
        }
        painter.rotate(angle);
    }
    //8.画标题和单位
    painter.resetTransform();//消除之前的旋转和坐标偏移
    painter.translate(width()/2,height()/2);//重新设置坐标偏移
    painter.setFont(QFont("黑体",w/24.444,75));
    painter.drawText(-w/15.56,h/6.0,QString::number(currentValue));
    painter.drawText(-w/14.66,h/4.4,name);
    painter.drawText(-w/29.333,h/3.14285,unit);
}













