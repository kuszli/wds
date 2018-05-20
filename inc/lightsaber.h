#ifndef LIGHTSABER_H
#define LIGHTSABER_H

#include <QObject>
#include <QWidget>
#include<QSlider>
#include<QDebug>
#include<QPushButton>
#include<QColorDialog>
#include<QVBoxLayout>
#include<QHBoxLayout>
#include<QLabel>
#include<QPixmap>
#include<QBitmap>
#include<QCoreApplication>
#include<QOpenGLWidget>
#include<QListWidget>
#include<QSpacerItem>
#include<inc/bluetoothconnectionwindow.h>
#include"inc/openglobj.h"
#include"inc/layout.h"

class Lightsaber : public QWidget
{
    Q_OBJECT

public:

    explicit Lightsaber(QWidget *parent = nullptr);
    int getLength(){return length;}
    int getSensivity(){return sensivity;}
    QColor getColor(){return color;}

signals:

public slots:
    void updateLength(int);
    void updateSensivity(int);
    void colorRed();
    void colorGreen();
    void colorBlue();
    void colorPurple();
    void colorYellow();
    void colorCustom();
    void connection();
    void disconnection();

private:
    QSlider* makeSlider(int min, int max, int pos);
    void makeColorButtons();
    int length;
    int sensivity;
    QColor color;
    BluetoothConnectionWindow* btWindow;
    OpenGLobj* model;
    //labels
    QLabel* info;
    QLabel* info2;
    QLabel* info3;
    //sliders
    QSlider* lengthSlider;
    QSlider* sensivitySlider;
    //buttons
    QPushButton* blueconnect;
    QPushButton* bluedisconnect;
    QPushButton* sabreOnOff;
    QPushButton* red;
    QPushButton* green;
    QPushButton* blue;
    QPushButton* purple;
    QPushButton* yellow;
    QPushButton* customButton;
};

#endif // LIGHTSABER_H
