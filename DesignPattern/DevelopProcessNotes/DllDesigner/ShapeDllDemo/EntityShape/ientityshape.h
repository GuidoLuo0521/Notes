#ifndef IENTITYSHAPE_H
#define IENTITYSHAPE_H

#include "../ShapeDllDemo_global.h"
#include "../globalDefine.h"

class SHAPEDLLDEMO_EXPORT IEntityShape
{
public:
    IEntityShape();

    static IEntityShape* create(ShapeType shape, ColorType color);

    virtual void draw() = 0;
};

#endif // IENTITYSHAPE_H
