#ifndef RECTSHAPE_H
#define RECTSHAPE_H

#include "ishapeinterface.h"

class RectShape : public IShapeInterface
{
public:
    RectShape();

    virtual void drawShape() override;
};

#endif // RECTSHAPE_H
