#include <QCoreApplication>

#include "Uncopyable.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

#if false
    Objcet o1;
    Objcet o2 = o1;
    Objcet o3(o2);
#endif


    return a.exec();
}
