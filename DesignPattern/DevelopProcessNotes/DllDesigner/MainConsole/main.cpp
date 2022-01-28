#include <QCoreApplication>
//#include "../DllDemo/abstractdlldemo.h"

#include "../ShapeDllDemo/EntityShape/ientityshape.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    //GetDllDemoInstance()->print();

    IEntityShape * entityShape = nullptr;

    entityShape = IEntityShape::create(ShapeType::Circle, ColorType::Red);
    entityShape->draw();

    entityShape = IEntityShape::create(ShapeType::Rectangle, ColorType::Red);
    entityShape->draw();

    entityShape = IEntityShape::create(ShapeType::Rectangle, ColorType::Yellow);
    entityShape->draw();

    entityShape = IEntityShape::create(ShapeType::Circle, ColorType::Green);
    entityShape->draw();

    entityShape = IEntityShape::create(ShapeType::Trangle, ColorType::Red);
    entityShape->draw();




    return a.exec();
}
