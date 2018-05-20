#include "inc/btclient.h"

BtClient::BtClient()
{
if(localDevice.isValid()){
    localDevice.powerOn();
    localDeviceName = localDevice.name();
    localDevice.setHostMode(QBluetoothLocalDevice::HostDiscoverable);
}
else throw "Missing bluetooth";
}

void BtClient::startDeviceDiscovery(){
    QBluetoothDeviceDiscoveryAgent *discoveryAgent = new QBluetoothDeviceDiscoveryAgent(this);
    connect(discoveryAgent, SIGNAL(deviceDiscovered(QBluetoothDeviceInfo)),this,SLOT(deviceDiscovered(QBluetoothDeviceInfo)));
    discoveryAgent->start();
}

void BtClient::startListening(){
    socket = new QBluetoothSocket(QBluetoothServiceInfo::RfcommProtocol);
    QString uuid = "550e8400-e29b-41d4-a716-446655440000";
    QString adress = "C4:43:8F:A5:F7:C3";
    socket->connectToService(QBluetoothAddress(adress), QBluetoothUuid(uuid), QIODevice::ReadOnly);
    connect(socket, SIGNAL(readyRead()), this, SLOT(readyToRead()));
}

void BtClient::deviceDiscovered(const QBluetoothDeviceInfo& device)
{
    qDebug() << "Found new device:" << device.name() << "(" << device.address().toString() << ")";
}

void BtClient::readyToRead(){
    char data[48];
    socket->readLine(data,48);
    printt(data);
}

void BtClient::printt(char* data){
  QString str = QString::fromLatin1(data);
  QString tmp;
  QChar aux;
  int i=0;
 // for(int i=0; i<3; ++i){
      aux=str.at(i);
      while(aux!='|'){
          aux=str.at(++i);
          tmp.append(aux);
        //  qDebug()<<aux;

      }
  //}
//   double d = str.toDouble();
    //qDebug()<< tmp;
// for(int i=0; i<8; ++i){
  //   qDebug() << data[i];
 //}
}
