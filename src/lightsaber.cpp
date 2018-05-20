#include "inc/lightsaber.h"

Lightsaber::Lightsaber(QWidget *parent) : QWidget(parent)
{
length = 100;
sensivity = 10;
color = QColor(120,120,120);
btWindow = nullptr;

lengthSlider = makeSlider(50,200,120);
connect(lengthSlider,SIGNAL(valueChanged(int)),this,SLOT(updateLength(int)));

sensivitySlider = makeSlider(5,100,80);
connect(sensivitySlider,SIGNAL(valueChanged(int)),this,SLOT(updateSensivity(int)));

makeColorButtons();

customButton = new QPushButton(tr("custom"),this);
customButton->adjustSize();
connect(customButton,SIGNAL(pressed()),this,SLOT(colorCustom()));

blueconnect = new QPushButton(tr("connect"), this);
blueconnect->adjustSize();
connect(blueconnect,SIGNAL(pressed()),this,SLOT(connection()));

bluedisconnect = new QPushButton(tr("disconnect"), this);
bluedisconnect->adjustSize();
connect(bluedisconnect,SIGNAL(pressed()),this,SLOT(disconnection()));


info = new QLabel(QString("color"), this);
info->setAlignment(Qt::AlignCenter);
info->adjustSize();

info2 = new QLabel(QString("length"), this);
info2->setAlignment(Qt::AlignCenter);
info2->adjustSize();

info3 = new QLabel(QString("sensitivity"), this);
info3->setAlignment(Qt::AlignCenter);
info3->adjustSize();


model = new OpenGLobj(this);

QSpacerItem* spring = new QSpacerItem(20,0,QSizePolicy::Expanding,QSizePolicy::Minimum );
QSpacerItem* zwischen = new QSpacerItem(20,0);
QHBoxLayout* layoutH = new QHBoxLayout;
layoutH->addItem(spring);
layoutH->addWidget(red);
layoutH->addWidget(green);
layoutH->addWidget(blue);
layoutH->addWidget(purple);
layoutH->addWidget(yellow);
layoutH->addItem(spring);
QHBoxLayout* conn = new QHBoxLayout;
conn->addItem(spring);
conn->addWidget(blueconnect);
conn->addItem(zwischen);
conn->addWidget(bluedisconnect);
conn->addItem(spring);
QHBoxLayout* cust = new QHBoxLayout;
cust->addItem(spring);
cust->addWidget(customButton);
cust->addItem(spring);
QVBoxLayout* layoutV = new QVBoxLayout;
layoutV->addSpacing(10);
layoutV->addLayout(conn);
layoutV->addWidget(info);
layoutV->addLayout(layoutH);
layoutV->addLayout(cust);
layoutV->addWidget(info2);
layoutV->addWidget(lengthSlider);
layoutV->addWidget(info3);
layoutV->addWidget(sensivitySlider);
layoutV->addSpacing(10);
QHBoxLayout* layoutM = new QHBoxLayout;
layoutM->addWidget(model);
layoutM->addLayout(layoutV);
setLayout(layoutM);



}


QSlider* Lightsaber::makeSlider(int min, int max, int pos){
    QSlider* slider = new QSlider(Qt::Horizontal, this);
    slider->setMinimum(min);
    slider->setMaximum(max);
    slider->setSliderPosition(pos);
    slider->adjustSize();
    return slider;
}


void Lightsaber::makeColorButtons(){

    red = new QPushButton(this);
    red->setStyleSheet("background-color: red");
    red->adjustSize();
    connect(red,SIGNAL(pressed()),this,SLOT(colorRed()));

    green = new QPushButton(this);
    green->setStyleSheet("background-color: green");
    green->adjustSize();
    connect(green,SIGNAL(pressed()),this,SLOT(colorGreen()));

    blue = new QPushButton(this);
    blue->setStyleSheet("background-color: blue");
    blue->adjustSize();
    connect(blue,SIGNAL(pressed()),this,SLOT(colorBlue()));

    purple = new QPushButton(this);
    purple->setStyleSheet("background-color: darkmagenta");
    purple->adjustSize();
    connect(purple,SIGNAL(pressed()),this,SLOT(colorPurple()));

    yellow = new QPushButton(this);
    yellow->setStyleSheet("background-color: yellow");
    yellow->adjustSize();
    connect(yellow,SIGNAL(pressed()),this,SLOT(colorYellow()));

}



void Lightsaber::updateLength(int len){
    length = len;
    model->scale(len);
}


void Lightsaber::updateSensivity(int sen){
    sensivity = sen;
    model->change_sensitivity(sen);
}

void Lightsaber::colorRed(){
color = QColor("red");
model->setColor(color);
}

void Lightsaber::colorGreen(){
color = QColor("green");
model->setColor(color);
}

void Lightsaber::colorBlue(){
color = QColor("blue");
model->setColor(color);
}

void Lightsaber::colorPurple(){
color = QColor("darkMagenta");
model->setColor(color);
}

void Lightsaber::colorYellow(){
color = QColor("yellow");
model->setColor(color);
}

void Lightsaber::colorCustom(){
color = QColorDialog::getColor(QColor("white"),this,tr("pick a color"));
QString qss = QString("background-color: %1").arg(color.name());
customButton->setStyleSheet(qss);
customButton->setDown(false);
model->setColor(color);
}

void Lightsaber::connection(){
btWindow = new BluetoothConnectionWindow;
btWindow->exec();
}


void Lightsaber::disconnection(){
if(btWindow)
    btWindow->breakConnection();
}
