#include "testthread.h"
#include "lazysingleton.h"
#include "eagersingleton.h"

const int gk_AutoIncrementCount = 50;


template<class T>
static void AutoIncrement(T& base)
{
    QElapsedTimer timer;
    timer.start();

    int i = gk_AutoIncrementCount;
    while ( i-- )
    {
        base.autoIncrement();
    }

    qDebug() << __FUNCTION__  << " : " << (double)timer.msecsSinceReference() / (double)1000;
}


static void EagerSingletonIncRef()
{
    AutoIncrement(EagerSingletonRef::instance());
}

static void EagerSingletonIncPtr()
{
    AutoIncrement(*EagerSingletonPtr::instance());
}

static void LazySingletonInc()
{
    AutoIncrement(*LazySingleton::instance());
}



////////
/// \brief ThreadEagerPtr::ThreadEagerPtr
///
ThreadEagerPtr::ThreadEagerPtr()
{

}

void ThreadEagerPtr::run()
{
    EagerSingletonIncPtr();
}

///
/// \brief ThreadEagerRef::ThreadEagerRef
///
ThreadEagerRef::ThreadEagerRef()
{

}

void ThreadEagerRef::run()
{
    //EagerSingletonIncRef();
    QElapsedTimer timer;
    timer.start();

    int i = gk_AutoIncrementCount;
    while ( i-- )
    {
        EagerSingletonRef::instance().autoIncrement();
    }

    qDebug() << __FUNCTION__  << " : " << (double)timer.msecsSinceReference() / (double)1000;
}



///
/// \brief ThreadLazy::ThreadLazy
///
ThreadLazy::ThreadLazy()
{

}

void ThreadLazy::run()
{
    //LazySingletonInc();

    QElapsedTimer timer;
    timer.start();

    int i = gk_AutoIncrementCount;
    while ( i-- )
    {
        LazySingleton::instance()->autoIncrement();
    }

    qDebug() << __FUNCTION__  << " : " << (double)timer.msecsSinceReference() / (double)1000;
}
