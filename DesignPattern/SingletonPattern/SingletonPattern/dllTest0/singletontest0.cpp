#include "singletontest0.h"
#include <QDebug>
#include "../dllDatabase/testbase.h"
#include "../dllDatabase/singleton.h"

SingletonTest0::SingletonTest0()
{

}

void SingletonTest0::printTest()
{
    qDebug() << "Singleton<TestBase>::getInstance() address : "
             << &Singleton<TestBase>::getInstance();
}
