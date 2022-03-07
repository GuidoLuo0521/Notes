#include "workerthread.h"

WorkerThread::WorkerThread(QObject *parent)
    : QThread(parent)
{

}

void WorkerThread::run()
{
    const int knOutVal = 100;
    const int knInVal  = 50000;

    for( int i = 0; i < knOutVal; ++i )
    {
        for(int j = 0; j < knInVal; ++j)

        emit sigProgress(i);
    }

    emit sigProgress(knOutVal);
}
