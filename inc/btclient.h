#ifndef BTCLIENT_H
#define BTCLIENT_H

#include <QBluetoothDeviceInfo>
#include <QBluetoothDeviceDiscoveryAgent>
#include <QBluetoothLocalDevice>
#include<QBluetoothSocket>
#include<QString>
#include <QtDebug>
#include<cstdlib>

class BtClient : public QObject
{
    Q_OBJECT
public:
    BtClient();
     void startDeviceDiscovery();
     void startListening();
     QBluetoothDeviceInfo getDev() {return currentDevice;}
signals:
     void newDevice();
public slots:
    void deviceDiscovered(const QBluetoothDeviceInfo&);
    void readyToRead();

private:
    QBluetoothLocalDevice localDevice;
    QString localDeviceName;
    void printt(char* data);
    QBluetoothSocket* socket;
    QBluetoothDeviceInfo currentDevice;

};

#endif // BTCLIENT_H
