#include <QCoreApplication>
#include "../DllDemo/abstractdlldemo.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    GetDllDemoInstance()->print();

    return a.exec();
}
