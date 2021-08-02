#ifndef WORKTHREAD_H
#define WORKTHREAD_H

#include <QThread>
#include <QDebug>

class WorkThread : public QThread
{
    Q_OBJECT

public:
    WorkThread(QObject *parent = nullptr);;

protected:
    void run() override;

private:
    const int m_knTotal = 5000;
};



#endif // WORKTHREAD_H

