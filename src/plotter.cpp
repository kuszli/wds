#include "inc/plotter.h"

Plotter::Plotter(QWidget* parent): QCustomPlot(parent){
}


Plotter::~Plotter(){

}

void Plotter::plot(){

}

void Plotter::realtimeDataSlot(){

}

AccPlotter::AccPlotter(QWidget *parent):
    Plotter(parent){

}

AccPlotter::~AccPlotter(){

}

void AccPlotter::plot(){
    addGraph();
    graph(0)->setPen(QPen(QColor(40,110,225)));
    graph(0)->setName("x");
    addGraph();
    graph(1)->setPen(QPen(QColor(255,110,40)));
    graph(1)->setName("y");
    addGraph();
    graph(2)->setPen(QPen(QColor(40,255,110)));
    graph(2)->setName("z");
    QSharedPointer<QCPAxisTickerTime> timeTicker(new QCPAxisTickerTime);
    timeTicker->setTimeFormat("%h:%m:%s");
    xAxis->setTicker(timeTicker);
    axisRect()->setupFullAxesBox();
    yAxis->setRange(-12,12);
    QCPTextElement* title = new QCPTextElement(this);
    title->setText(tr("Accelerometer output"));
    plotLayout()->insertRow(0);
    plotLayout()->addElement(0,0,title);
    xAxis->setLabel(tr("time"));
    yAxis->setLabel(tr("acceleration"));
    legend->setVisible(true);
    connect(xAxis, SIGNAL(rangeChanged(QCPRange)),xAxis2, SLOT(setRange(QCPRange)));
    connect(yAxis, SIGNAL(rangeChanged(QCPRange)),yAxis2, SLOT(setRange(QCPRange)));
    connect(&dataTimer, SIGNAL(timeout()), this, SLOT(realtimeDataSlot()));
    dataTimer.start(10);

}

void AccPlotter::realtimeDataSlot(){
    static QTime time(QTime::currentTime());
    double key = time.elapsed()/1000.0;
    static double lastPointKey = 0;
    if(key-lastPointKey>0.002)
    {
        graph(0)->addData(key,BluetoothConnectionWindow::accX);
        graph(1)->addData(key,BluetoothConnectionWindow::accY);
        graph(2)->addData(key,BluetoothConnectionWindow::accZ);
        lastPointKey=key;
    }

    xAxis->setRange(key,8,Qt::AlignRight);
    replot();
}

GyroPlotter::GyroPlotter(QWidget *parent):
    Plotter(parent){

}

GyroPlotter::~GyroPlotter(){

}

void GyroPlotter::plot(){
    addGraph();
    graph(0)->setPen(QPen(QColor(40,110,225)));
    graph(0)->setName("x");
    addGraph();
    graph(1)->setPen(QPen(QColor(255,110,40)));
    graph(1)->setName("y");
    addGraph();
    graph(2)->setPen(QPen(QColor(40,255,110)));
    graph(2)->setName("z");
    QSharedPointer<QCPAxisTickerTime> timeTicker(new QCPAxisTickerTime);
    timeTicker->setTimeFormat("%h:%m:%s");
    xAxis->setTicker(timeTicker);
    axisRect()->setupFullAxesBox();
    yAxis->setRange(-12,12);
    QCPTextElement* title = new QCPTextElement(this);
    title->setText(tr("Gyroscope output"));
    plotLayout()->insertRow(0);
    plotLayout()->addElement(0,0,title);
    xAxis->setLabel(tr("time"));
    yAxis->setLabel(tr("angular velocity"));
    legend->setVisible(true);
    connect(xAxis, SIGNAL(rangeChanged(QCPRange)),xAxis2, SLOT(setRange(QCPRange)));
    connect(yAxis, SIGNAL(rangeChanged(QCPRange)),yAxis2, SLOT(setRange(QCPRange)));
    connect(&dataTimer, SIGNAL(timeout()), this, SLOT(realtimeDataSlot()));
    dataTimer.start(10);

}

void GyroPlotter::realtimeDataSlot(){
    static QTime time(QTime::currentTime());
    double key = time.elapsed()/1000.0;
    static double lastPointKey = 0;
    if(key-lastPointKey>0.002)
    {
        graph(0)->addData(key,BluetoothConnectionWindow::gyroX);
        graph(1)->addData(key,BluetoothConnectionWindow::gyroY);
        graph(2)->addData(key,BluetoothConnectionWindow::gyroZ);
        lastPointKey=key;
    }

    xAxis->setRange(key,8,Qt::AlignRight);
    replot();
}

Plots::Plots(QWidget* parent):
    QWidget(parent){
    QVBoxLayout* layout = new QVBoxLayout;
    QHBoxLayout* Clup = new QHBoxLayout;
    QHBoxLayout* Cldwn = new QHBoxLayout;

    plotAcc = new AccPlotter(this);
    plotGyro = new GyroPlotter(this);
    QPushButton* ButtonUp = new QPushButton(tr("Clear"),this);
    QPushButton* ButtonDwn = new QPushButton(tr("Clear"),this);

    QSpacerItem* spacer = new QSpacerItem(30,0,QSizePolicy::Expanding,QSizePolicy::Minimum);

    Clup->addItem(spacer);
    Clup->addWidget(ButtonUp);
    Clup->addItem(spacer);

    Cldwn->addItem(spacer);
    Cldwn->addWidget(ButtonDwn);
    Cldwn->addItem(spacer);

    layout->addWidget(plotAcc);
    layout->addLayout(Clup);
    layout->addWidget(plotGyro);
    layout->addLayout(Cldwn);

    plotAcc->plot();
    plotGyro->plot();
    setLayout(layout);
    connect(ButtonUp, SIGNAL(pressed()), this, SLOT(onClearClickAcc()));
    connect(ButtonDwn, SIGNAL(pressed()), this, SLOT(onClearClickGyro()));

}

Plots::~Plots(){}

void Plots::onClearClickAcc(){
    plotAcc->graph(0)->data()->clear();
    plotAcc->graph(1)->data()->clear();
    plotAcc->graph(2)->data()->clear();
    plotAcc->replot();

}

void Plots::onClearClickGyro(){
    plotGyro->graph(0)->data()->clear();
    plotGyro->graph(1)->data()->clear();
    plotGyro->graph(2)->data()->clear();
    plotGyro->replot();

}
