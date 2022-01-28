#ifndef GLOBALDEFINE_H
#define GLOBALDEFINE_H

#include <QDebug>
#include <QSharedPointer>

#define OUT_PUT_MSG qDebug() << __FILE__ << __FUNCTION__


#define OUT_PUT_MSG_FUN() \
{ \
    qDebug() << __FILE__ << __FUNCTION__; \
}

enum class ShapeType
{
    Circle,
    Rectangle,
    Trangle
};

enum class ColorType
{
    Red,
    Green,
    TeaGreen,
    Yellow,
    Blue,
    Pink,
    flowerBlue
};


#endif // GLOBALDEFINE_H
