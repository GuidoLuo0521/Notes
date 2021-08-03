#include "customthread.h"

#include "Common.h"
#include <QDebug>

CustomThread::CustomThread()
{

}

void CustomThread::run()
{

#if 1
    while(g_UserdBufferindex < g_DataSize)
    {
        g_UsedBytes.acquire();

        g_Mutex.lock();
        qDebug() << currentThreadId() << " : " << g_Buffer[g_UserdBufferindex % 80];
        ++g_UserdBufferindex;
        g_Mutex.unlock();

        g_FreeBytes.release();

    }
#else // 单线程使用
    for( int i = 0; i < g_DataSize ; ++i)
    {
        g_UsedBytes.acquire();

        qDebug() << currentThreadId() << " : " << g_Buffer[i % 80];

        g_FreeBytes.release();
    }
#endif
}
