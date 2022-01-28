#ifndef GREENCOLOR_H
#define GREENCOLOR_H
#include "icolorinterface.h"

class GreenColor : public IColorInterface
{
public:
    GreenColor();

    virtual void drawColor() override;
};

#endif // GREENCOLOR_H
