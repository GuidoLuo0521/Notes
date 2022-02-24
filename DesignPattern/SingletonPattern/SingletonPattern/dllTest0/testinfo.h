#ifndef TESTINFO_H
#define TESTINFO_H

#include <QtCore>
#include "dllTest0_global.h"

class DLLTEST0_EXPORT TestInfo
{
public:
    TestInfo();

    QString name() const;
    void setName(const QString& name);
    void printName() const;

private:
    QString m_name;
};

DLLTEST0_EXPORT extern TestInfo sg_TestInfo;



#endif // TESTINFO_H
