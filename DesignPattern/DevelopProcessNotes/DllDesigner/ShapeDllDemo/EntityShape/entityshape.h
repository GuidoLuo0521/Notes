#ifndef ENTITYSHAPE_H
#define ENTITYSHAPE_H

#include "ientityshape.h"
#include <QSharedPointer>

class IShapeInterface;
class IColorInterface;

class EntityShape : public IEntityShape
{
public:
    EntityShape(ShapeType shape, ColorType color);

    virtual void draw() override;

protected:
    QSharedPointer<IShapeInterface> m_shape;
    QSharedPointer<IColorInterface> m_color;
};

#endif // ENTITYSHAPE_H
