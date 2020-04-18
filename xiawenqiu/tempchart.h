#ifndef TEMPCHART_H
#define TEMPCHART_H

#include <QWidget>
#include "chart.h"

class TempChart : public QWidget
{
    Q_OBJECT
public:
    explicit TempChart(QWidget *parent = nullptr);

signals:

public slots:
public:
    Chart    *tempchart;

};

#endif // TEMPCHART_H
