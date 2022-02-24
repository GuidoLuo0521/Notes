#include "testinfo.h"

TestInfo sg_TestInfo;

TestInfo::TestInfo()
    : m_name("TestInfo")
{

}

QString TestInfo::name() const
{
    return m_name;
}

void TestInfo::setName(const QString &name)
{
    m_name = name;
}

void TestInfo::printName() const
{
    qDebug() << "DllTest0 sg_TestInfo address : "<< &sg_TestInfo;
    qDebug() << m_name << "\n";
}
