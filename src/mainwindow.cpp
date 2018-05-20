#include "inc/mainwindow.h"


MainWindow::MainWindow(QWidget* parent): QMainWindow(parent)
{
Lightsaber* windowElements = new Lightsaber;
QTabWidget* tabs = new QTabWidget(this);
Plots* plots = new Plots(this);

tabs->addTab(windowElements,tr("animation"));
tabs->addTab(plots,tr("plots"));
setCentralWidget(tabs);
setWindowTitle("Lightsaber");
}

