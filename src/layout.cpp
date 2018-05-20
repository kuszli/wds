#include "inc/layout.h"

Layout::Layout()
{

}

bool Layout::hasHeightForWidth() const
{
    return true;
}

int Layout::heightForWidth(int w) const
{
    return w;
}

