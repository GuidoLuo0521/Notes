#ifndef CUSTOMTHREAD_H
#define CUSTOMTHREAD_H

#include <QThread>

class CustomThread :  public QThread
{
    Q_OBJECT
public:
    CustomThread();

protected:
    void run() override;
};

#endif // CUSTOMTHREAD_H
