#include "entityshape.h"
#include "../Shape/ishapeinterface.h"
#include "../Color/icolorinterface.h"

EntityShape::EntityShape(ShapeType shape, ColorType color)
    : m_shape(IShapeInterface::create(shape))
    , m_color(IColorInterface::create(color))
{

}

void EntityShape::draw()
{
    m_color->drawColor();
    m_shape->drawShape();

    qDebug() << "\n";
}
