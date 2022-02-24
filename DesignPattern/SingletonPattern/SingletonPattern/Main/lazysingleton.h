#ifndef LAZYSINGLETON_H
#define LAZYSINGLETON_H

#include "../dllDatabase/testbase.h"

//
// 懒汉模式，延迟加载
//
class LazySingleton : public TestBase
{
public:
    static LazySingleton* instance();
private:
    LazySingleton();

private:
    static LazySingleton * m_instance;
};

#endif // LAZYSINGLETON_H
