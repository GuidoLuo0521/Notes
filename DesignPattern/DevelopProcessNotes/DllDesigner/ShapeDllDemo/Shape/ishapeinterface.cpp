#include "ishapeinterface.h"
#include "Shape/circleshape.h"
#include "Shape/rectshape.h"
#include "Shape/triangleshape.h"

IShapeInterface::IShapeInterface()
{

}

QSharedPointer<IShapeInterface> IShapeInterface::create(ShapeType shape)
{
    switch (shape) {
    case ShapeType::Circle: return QSharedPointer<IShapeInterface>(new CircleShape);
    case ShapeType::Trangle: return QSharedPointer<IShapeInterface>(new TrangleShape);
    case ShapeType::Rectangle: return QSharedPointer<IShapeInterface>(new RectShape);
    default: return nullptr;
    }
}

