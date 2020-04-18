#ifndef HUMCHART_H
#define HUMCHART_H

#include <QWidget>
#include "chart.h"

class HumChart : public QWidget
{
    Q_OBJECT
public:
    explicit HumChart(QWidget *parent = nullptr);

signals:

public slots:
public:
    Chart    *humchart;
};

#endif // HUMCHART_H
