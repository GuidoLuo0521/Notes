#ifndef REDCOLOR_H
#define REDCOLOR_H

#include "icolorinterface.h"

class RedColor : public IColorInterface
{
public:
    RedColor();

    virtual void drawColor() override;
};

#endif // REDCOLOR_H
