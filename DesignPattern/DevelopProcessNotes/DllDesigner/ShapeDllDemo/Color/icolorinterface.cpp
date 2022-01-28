#include "icolorinterface.h"

#include "Color/redcolor.h"
#include "Color/bluecolor.h"
#include "Color/greencolor.h"
#include "Color/yellowcolor.h"

IColorInterface::IColorInterface()
{

}
QSharedPointer<IColorInterface> IColorInterface::create(ColorType color)
{
    switch (color) {
    case ColorType::Red: return QSharedPointer<IColorInterface>(new RedColor);
    case ColorType::Green: return QSharedPointer<IColorInterface>(new GreenColor);
    case ColorType::Yellow: return QSharedPointer<IColorInterface>(new YellowColor);
    case ColorType::Blue: return QSharedPointer<IColorInterface>(new BlueColor);

    default: return nullptr;
    }
}
