#include "common.h"
#include "lazysingleton.h"

#include <QMutex>
#include <QMutexLocker>
#include <QElapsedTimer>

LazySingleton * LazySingleton::m_instance;

LazySingleton::LazySingleton()
{
    PRINT_FUNC_NAME;
}

#if 0   // 基础班不加锁
// 演示懒汉模式多线程调用崩溃情况

LazySingleton* LazySingleton::instance()
{
    if(nullptr == m_instance)
    {
        m_instance = new LazySingleton;
    }

    TEST_MSG("LazySingleton address : ", m_instance);
    return m_instance;
}


#elif 0     // 加锁 v1.0

QMutex g_mutex;
LazySingleton* LazySingleton::instance()
{
    QMutexLocker locker(&g_mutex);
    if(nullptr == m_instance)
    {
        m_instance = new LazySingleton;
    }

    TEST_MSG("LazySingleton address : ", m_instance);
    return m_instance;
}

#else

QMutex g_mutex;
LazySingleton* LazySingleton::instance()
{
    // 当第一个线程运行到这里时，此时会对locker对象 "加锁"，
    // 当第二个线程运行该方法时，首先检测到locker对象为"加锁"状态，该线程就会挂起等待第一个线程解锁
    // lock语句运行完之后（即线程运行完之后）会对该对象"解锁"
    // 双重锁定只需要一句判断就可以了

    if(nullptr == m_instance)
    {
        QMutexLocker locker(&g_mutex);
        if(nullptr == m_instance)
        {
            m_instance = new LazySingleton;
        }
    }

    TEST_MSG("LazySingleton address : ", m_instance);
    return m_instance;
}



#endif
