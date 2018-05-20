#include<QApplication>
#include<QWidget>
#include<QLabel>
#include<QPushButton>
#include<QSlider>
#include<QBluetoothSocket>
#include<QString>
#include<inc/mainwindow.h>


int main(int argc, char* argv[]){
    QApplication app(argc, argv);
    MainWindow* okno = new MainWindow();
    okno->show();
    return app.exec();
}
