#ifndef PLOTTER_H
#define PLOTTER_H

#include "qcustomplot.h"
#include"bluetoothconnectionwindow.h"
#include<QVBoxLayout>
#include<QHBoxLayout>
#include<QTime>
#include<QTimer>
#include<QPushButton>
#include<QSpacerItem>


class Plotter: public QCustomPlot {
    Q_OBJECT
public:
    Plotter(QWidget* parent);
    ~Plotter();
    void plot();
signals:

public slots:
    void realtimeDataSlot();
private:
   QTimer dataTimer;
};


class AccPlotter: public Plotter{
    Q_OBJECT
public:
    AccPlotter(QWidget* parent);
    ~AccPlotter();
    void plot();
signals:
public slots:
    void realtimeDataSlot();
private:
   QTimer dataTimer;
};


class GyroPlotter: public Plotter{
    Q_OBJECT
public:
    GyroPlotter(QWidget* parent);
    ~GyroPlotter();
    void plot();
signals:
public slots:
    void realtimeDataSlot();
private:
   QTimer dataTimer;
};


class Plots: public QWidget{
    Q_OBJECT
public:
    Plots(QWidget* parent);
    ~Plots();
public slots:
    void onClearClickAcc();
    void onClearClickGyro();
private:
    AccPlotter* plotAcc;
    GyroPlotter* plotGyro;


};

#endif // PLOTTER_H
