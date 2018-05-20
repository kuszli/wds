#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include<QMainWindow>
#include <QObject>
#include<QWidget>
#include<QPushButton>
#include<QTabWidget>
#include"inc/lightsaber.h"
#include<QHBoxLayout>
#include"inc/plotter.h"

class MainWindow: public QMainWindow
{
public:
    MainWindow(QWidget* parent = nullptr);
};

class Widgets: public QWidget{
public:
    Widgets(QWidget* parent = nullptr);
};

#endif // MAINWINDOW_H
