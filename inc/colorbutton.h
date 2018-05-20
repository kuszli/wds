#ifndef COLORBUTTON_H
#define COLORBUTTON_H

#include <QWidget>

class Colorbutton : public Qwidget
{
    Q_OBJECT

    QColor color;

public:
    explicit Colorbutton(QWidget *parent = nullptr);
    QColor getColor(){return color;}
    void setColor(QColor cl){color = cl;}
signals:

public slots:

};

#endif // COLORBUTTON_H
