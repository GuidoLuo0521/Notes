#ifndef COMMON_H
#define COMMON_H

#include <QSemaphore>   // 信号量控制
#include <QMutex>


// 生产者消费者的公用量

// 总共生产1000个数据
const int g_DataSize = 1000;
// 当前缓冲区总数
const int g_BufferSize = 80;
// 缓冲区
extern int g_Buffer[g_BufferSize];
// 多线程消费者控制量
extern int g_UserdBufferindex ;
// 多线程消费者控制量互斥量
extern QMutex g_Mutex;
// 当前空闲的可用的信号量
extern QSemaphore g_FreeBytes;
// 当前已用的信号量
extern QSemaphore g_UsedBytes;


#endif // COMMON_H
