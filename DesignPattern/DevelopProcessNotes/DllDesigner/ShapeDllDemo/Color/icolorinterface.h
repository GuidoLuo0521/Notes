#ifndef ICOLORINTERFACE_H
#define ICOLORINTERFACE_H
#include "globalDefine.h"

class IColorInterface
{
public:
    IColorInterface();

    virtual void drawColor() = 0;

    static QSharedPointer<IColorInterface> create(ColorType color);
};

#endif // ICOLORINTERFACE_H
