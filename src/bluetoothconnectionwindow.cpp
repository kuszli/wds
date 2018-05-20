#include "inc/bluetoothconnectionwindow.h"

double BluetoothConnectionWindow::accX=0;
double BluetoothConnectionWindow::accY=0;
double BluetoothConnectionWindow::accZ=0;
double BluetoothConnectionWindow::gyroX=0;
double BluetoothConnectionWindow::gyroY=0;
double BluetoothConnectionWindow::gyroZ=0;


BluetoothConnectionWindow::BluetoothConnectionWindow() : QDialog(nullptr)
{

    devicesList = new QListWidget(this);
    QLabel* lab = new QLabel(tr("select bluetooth device"), this);
    QVBoxLayout* layoutV = new QVBoxLayout;
    layoutV->addWidget(lab);
    layoutV->addWidget(devicesList);
    setLayout(layoutV);
    setWindowTitle(tr("Bluetooth connection"));

if(localDevice.isValid()){
    localDevice.powerOn();
    localDeviceName = localDevice.name();
    localDevice.setHostMode(QBluetoothLocalDevice::HostDiscoverable);
    connect(devicesList, SIGNAL(itemDoubleClicked(QListWidgetItem*)), this, SLOT(deviceSelected(QListWidgetItem*)));
    startDeviceDiscovery();
}
    else{
    QMessageBox* warning = new QMessageBox();
    warning->setInformativeText("Bluetooth disconnected!");
    warning->exec();

    }


}


void BluetoothConnectionWindow::startDeviceDiscovery(){
    QBluetoothDeviceDiscoveryAgent *discoveryAgent = new QBluetoothDeviceDiscoveryAgent(this);
    connect(discoveryAgent, SIGNAL(deviceDiscovered(QBluetoothDeviceInfo)),this,SLOT(deviceDiscovered(QBluetoothDeviceInfo)));
    discoveryAgent->start();
}


void BluetoothConnectionWindow::startListening(){
    socket = new QBluetoothSocket(QBluetoothServiceInfo::RfcommProtocol);
    QString uuid = "550e8400-e29b-41d4-a716-446655440000";
    socket->connectToService(QBluetoothAddress(remoteDeviceAdress), QBluetoothUuid(uuid), QIODevice::ReadOnly);
    connect(socket, SIGNAL(readyRead()), this, SLOT(readyToRead()));
    connect(socket,SIGNAL(error(QBluetoothSocket::SocketError)),this,SLOT(errorHandle()));
}


void BluetoothConnectionWindow::readyToRead(){
    char data[64];
    socket->readLine(data,64);
    printt(data);
}

void BluetoothConnectionWindow::printt(char* data){
   QString str = QString::fromLatin1(data);
   QString tmp[6];
   QChar aux;
   int j=0;
   for(int i=0; i<6; ++i){
        while(str.at(j)!='|'){
            if(str.at(j)==','){
                aux='.';
            }
            else{
            aux=str.at(j);
            }
            tmp[i].append(aux);
             ++j;
         }
        ++j;
   }

    accX=tmp[0].toDouble();
    accY=tmp[1].toDouble();
    accZ=tmp[2].toDouble();
    gyroX=tmp[3].toDouble();
    gyroY=tmp[4].toDouble();
    gyroZ=tmp[5].toDouble();
    qDebug() << accX;


}


void BluetoothConnectionWindow::deviceSelected(QListWidgetItem* item){
    remoteDeviceAdress = item->data(Qt::UserRole).toString();
    qDebug() << remoteDeviceAdress;
    startListening();
}

void BluetoothConnectionWindow::deviceDiscovered(const QBluetoothDeviceInfo& device)
{
    QListWidgetItem* item = new QListWidgetItem;
    item->setText(device.name());
    item->setData(Qt::UserRole, device.address().toString());
    devicesList->insertItem(devicesList->count(),item);

}

void BluetoothConnectionWindow::errorHandle(){
    qDebug() << socket->errorString();
}

void BluetoothConnectionWindow::breakConnection(){
    socket->disconnectFromService();
}
