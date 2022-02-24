#ifndef COMMON_H
#define COMMON_H

#include <QtCore>
#include <QThread>
#include <QMutex>
#include <QElapsedTimer>

#define PRINT_FUNC_NAME qDebug() << __FUNCTION__

#define PRINT_THREADID qDebug() << __FUNCTION__ << " : " << QThread::currentThreadId()

#define CURRENT_THREADID QThread::currentThreadId()


#define TEST_MSG(name , ptr) qDebug() << "CurrentThreadID:" << CURRENT_THREADID << name << ptr;

#endif // COMMON_H
