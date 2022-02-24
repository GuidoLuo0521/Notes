#ifndef TESTBASE_H
#define TESTBASE_H

#include "dllDatabase_global.h"


class DLLDATABASE_EXPORT TestBase
{
public:
    TestBase();
    virtual ~TestBase();

    int test();
    void setTest(const int test);
    void autoIncrement();
    void printTest();
private:
    int m_test;
};






#endif // TESTBASE_H
