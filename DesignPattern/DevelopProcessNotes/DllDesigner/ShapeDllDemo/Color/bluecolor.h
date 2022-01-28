#ifndef BLUECOLOR_H
#define BLUECOLOR_H

#include "icolorinterface.h"

class BlueColor : public IColorInterface
{
public:
    BlueColor();

    virtual void drawColor() override;
};

#endif // BLUECOLOR_H
