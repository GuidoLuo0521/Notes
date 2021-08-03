#include "Common.h"

int g_Buffer[g_BufferSize];

int g_UserdBufferindex = 0;

QMutex g_Mutex;

// 当前空闲的可用的信号量
QSemaphore g_FreeBytes(g_BufferSize);
// 当前已用的信号量
QSemaphore g_UsedBytes(0);
