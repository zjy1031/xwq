#ifndef SHOWDATA_H
#define SHOWDATA_H
/*仪表盘*/
#include <QWidget>
#include<QPainter>//画家类
#include<QPaintEvent>//绘制事件
#include<QPointF>//double类型的坐标点
#include<QLinearGradient>//渐变效果

class ShowData : public QWidget
{
    Q_OBJECT
public:
    explicit ShowData(QWidget *parent = nullptr);
    void setData(double data);
    void setMaxAndMin(int max,int min);
    void setName(QString name,QString unit);
protected:
    void paintEvent(QPaintEvent *event);//绘制事件或重绘函数
signals:

public slots:
private:
    double max;
    double min;
    double currentValue;
    QString name;
    QString unit;//单位
    QPointF point[3];
    QPointF point2[3];

};

#endif // SHOWDATA_H
