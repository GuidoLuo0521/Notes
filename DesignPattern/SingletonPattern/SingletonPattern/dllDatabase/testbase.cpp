#include <QDebug>
#include "testbase.h"

TestBase::TestBase()
    : m_test(0)
{

}

TestBase::~TestBase()
{

}


int TestBase::test()
{
    return m_test;
}

void TestBase::setTest(const int test)
{
    m_test = test;
}

void TestBase::autoIncrement()
{
    m_test += 1;
}

void TestBase::printTest()
{
    qDebug() << m_test;
}
