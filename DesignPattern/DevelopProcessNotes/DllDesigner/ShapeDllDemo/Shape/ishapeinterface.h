#ifndef ISHAPEINTERFACE_H
#define ISHAPEINTERFACE_H

#include "ShapeDllDemo_global.h"
#include "globalDefine.h"

class IShapeInterface
{

public:
    IShapeInterface();

    static QSharedPointer<IShapeInterface> create(ShapeType shape);

    virtual void drawShape() = 0;

};

#endif // ISHAPEINTERFACE_H
