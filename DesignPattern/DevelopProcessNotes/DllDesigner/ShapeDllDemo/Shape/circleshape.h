#ifndef CIRCLESHAPE_H
#define CIRCLESHAPE_H

#include "ishapeinterface.h"

class CircleShape : public IShapeInterface
{
public:
    CircleShape();

    virtual void drawShape() override;
};

#endif // CIRCLESHAPE_H
