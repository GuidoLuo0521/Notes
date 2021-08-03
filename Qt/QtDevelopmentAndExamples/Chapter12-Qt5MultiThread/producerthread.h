#ifndef PRODUCERTHREAD_H
#define PRODUCERTHREAD_H

#include <QThread>

class ProducerThread : public QThread
{
    Q_OBJECT
public:
    ProducerThread();

protected:
    void run() override;
};

#endif // PRODUCERTHREAD_H
