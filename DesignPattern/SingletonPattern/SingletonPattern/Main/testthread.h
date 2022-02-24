#ifndef TEST_THREAD_H
#define TEST_THREAD_H
#include "common.h"

class ThreadEagerPtr : public QThread
{
public:
    ThreadEagerPtr();

protected:
    virtual void run() override;
};

class ThreadEagerRef : public QThread
{
public:
    ThreadEagerRef();

protected:
    virtual void run() override;
};



class ThreadLazy : public  QThread
{
public:
    ThreadLazy();

protected:
    virtual void run() override;
};

#endif // THREAD_H
