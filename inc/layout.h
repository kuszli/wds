#ifndef LAYOUT_H
#define LAYOUT_H

#include<QHBoxLayout>

class Layout: public QHBoxLayout
{
public:
    Layout();
protected:
    bool hasHeightForWidth() const;
    int heightForWidth(int) const;
};

#endif // LAYOUT_H
