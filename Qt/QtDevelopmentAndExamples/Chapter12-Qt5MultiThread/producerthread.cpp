#include "producerthread.h"

#include "Common.h"
#include <QDebug>

ProducerThread::ProducerThread()
{

}

void ProducerThread::run()
{
    // 生产者负责生产
    int val = 0;
    for( int i = 0; i < g_DataSize; ++i)
    {
        // 如果有空闲的缓冲区，请求一个
        g_FreeBytes.acquire();

        // 缓冲区赋值
        val = i % 80;
        g_Mutex.lock();
        g_Buffer[val] = val;
        g_Mutex.unlock();

        // 释放一个可以使用的缓冲区
        g_UsedBytes.release();
    }
}
