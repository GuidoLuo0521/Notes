#include "dlltest1.h"

#include "../dllTest0/testinfo.h"


DllTest1 sg_DllTest1 = DllTest1(sg_TestInfo);


DllTest1::DllTest1()
{
    sg_TestInfo.printName();
}

DllTest1::DllTest1(const TestInfo &info)
    : m_name(info.name())
{

}

void DllTest1::setTestName(const QString &name)
{
    sg_TestInfo.setName(name);
}

void DllTest1::printName() const
{
    qDebug() << "DllTest1 sg_TestInfo address : "<< &sg_TestInfo;
    sg_TestInfo.printName();
}

