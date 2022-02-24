#include "singletontest1.h"
#include "../dllDatabase/testbase.h"
#include "../dllDatabase/singleton.h"

SingletonTest1::SingletonTest1()
{

}

void SingletonTest1::printTest()
{
    qDebug() << "Singleton<TestBase>::getInstance() address : "
             << &Singleton<TestBase>::getInstance();

}
