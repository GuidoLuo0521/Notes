#ifndef DLLTEST1_H
#define DLLTEST1_H

#include <QtCore>
#include "dllTest1_global.h"


class TestInfo;

class DLLTEST1_EXPORT DllTest1
{
public:
    DllTest1();
    DllTest1(const TestInfo& info);

    void setTestName(const QString& name);
    void printName() const;

private:
    QString m_name;

};

DLLTEST1_EXPORT extern DllTest1 sg_DllTest1;



#endif // DLLTEST1_H
