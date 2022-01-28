#include "ientityshape.h"
#include "entityshape.h"

IEntityShape::IEntityShape()
{

}

IEntityShape *IEntityShape::create(ShapeType shape, ColorType color)
{
    return new EntityShape(shape, color);
}
