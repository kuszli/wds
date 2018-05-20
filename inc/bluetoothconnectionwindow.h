#ifndef BLUETOOTHCONNECTIONWINDOW_H
#define BLUETOOTHCONNECTIONWINDOW_H

#include<QDialog>
#include<QListWidget>
//#include<src/bluetoothdeviceitem.h>
#include<QVBoxLayout>
#include<QDebug>
#include<QBluetoothDeviceInfo>
#include<QBluetoothDeviceDiscoveryAgent>
#include<QBluetoothLocalDevice>
#include<QBluetoothSocket>
#include<QString>
#include<QtDebug>
#include<QLabel>
#include<QMessageBox>


class BluetoothConnectionWindow : public QDialog
{
    Q_OBJECT
public:
    BluetoothConnectionWindow();
    void startDeviceDiscovery();
    void startListening();
    void breakConnection();
    static double accX;
    static double accY;
    static double accZ;
    static double gyroX;
    static double gyroY;
    static double gyroZ;

signals:

public slots:
   void deviceSelected(QListWidgetItem* item);
   void deviceDiscovered(const QBluetoothDeviceInfo&);
   void readyToRead();
   void errorHandle();
protected:
     QSize sizeHint() const{return QSize(300,300);}
private:
   QBluetoothLocalDevice localDevice;
   QString localDeviceName;
   QBluetoothSocket* socket;
   void printt(char* data);
   QListWidget* devicesList;
   QString remoteDeviceAdress;
};

#endif // BLUETOOTHCONNECTIONWINDOW_H
