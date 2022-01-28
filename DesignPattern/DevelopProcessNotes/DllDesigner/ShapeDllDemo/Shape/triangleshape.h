#ifndef TRIANGLESHAPE_H
#define TRIANGLESHAPE_H

#include "ishapeinterface.h"

class TrangleShape : public IShapeInterface
{
public:
    TrangleShape();

    virtual void drawShape() override;
};

#endif // TRIANGLESHAPE_H
