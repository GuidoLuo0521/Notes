#ifndef EAGERSINGLETON_H
#define EAGERSINGLETON_H

#include "../dllDatabase/testbase.h"

class EagerSingletonRef : public TestBase
{
public:
    static EagerSingletonRef& instance();

private:
    EagerSingletonRef();
    static EagerSingletonRef m_instance;

};

class EagerSingletonPtr : public TestBase
{
public:
    static EagerSingletonPtr* instance();

private:
    EagerSingletonPtr();
    static EagerSingletonPtr m_instance;

};




#endif // EAGERSINGLETON_H
