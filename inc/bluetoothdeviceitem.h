#ifndef BLUETOOTHDEVICEITEM_H
#define BLUETOOTHDEVICEITEM_H

#include<QListWidgetItem>
#include<QString>

class BluetoothDeviceItem : public QListWidgetItem
{
public:
    BluetoothDeviceItem();
    QString getDeviceAddress(){return deviceAddress;}
    void setDeviceAddress(QString adress){deviceAddress = adress;}
private:
    QString deviceAddress;
};

#endif // BLUETOOTHDEVICEITEM_H
