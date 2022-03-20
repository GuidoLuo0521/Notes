#include <QCoreApplication>

#include "constructortest.h"
#include "slicingobject.h"


int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

#if false
    PrimarySchoolStudent s;
    s.name = "yes";
    func(s);
#endif


    WindowWithScrollbars w;
    //w.m_name = "testWindow";
    printNameAndDisplay(w);

    //printNameAndDisplayRef(w);

    return a.exec();
}
