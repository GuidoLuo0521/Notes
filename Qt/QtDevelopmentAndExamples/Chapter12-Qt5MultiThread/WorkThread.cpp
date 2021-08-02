#include "WorkThread.h"


WorkThread::WorkThread(QObject *parent) : QThread(parent){}

void WorkThread::run()
{
    int i = 0;
    while (m_knTotal > ++i)
    {
        for( int j = 0; j < 10; ++j )
            qDebug() << j << j << j << j << j << j << j << j << j << j;
    }
}
