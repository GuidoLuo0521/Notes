#include <QCoreApplication>

#include "VirtualDestructorsTest.h"
#include "PureVirtualDestructors.h"




int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    std::cout << "Hello World!\n";

    VA* p = new VB;

    delete p;

    return a.exec();
}
