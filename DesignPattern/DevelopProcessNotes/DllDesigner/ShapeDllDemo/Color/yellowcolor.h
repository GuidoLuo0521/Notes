#ifndef YELLOWCOLOR_H
#define YELLOWCOLOR_H

#include "icolorinterface.h"

class YellowColor : public IColorInterface
{
public:
    YellowColor();

    virtual void drawColor() override;
};

#endif // YELLOWCOLOR_H
