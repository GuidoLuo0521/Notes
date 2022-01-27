#include "dlldemo.h"
#include <QDebug>

IAbstractDllDemo* GetDllDemoInstance()
{
    return &DllDemo::GetInstance();
}


DllDemo& DllDemo::GetInstance()
{
    static DllDemo demo;
    return demo;
}

DllDemo::DllDemo()
{
}

DllDemo::~DllDemo()
{

}

void DllDemo::print()
{
    qDebug() << __FILE__ << __FUNCTION__;
}
