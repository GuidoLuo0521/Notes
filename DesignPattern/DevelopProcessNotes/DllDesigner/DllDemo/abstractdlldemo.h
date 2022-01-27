#ifndef ABSTRACTDLLDEMO_H
#define ABSTRACTDLLDEMO_H

#include "DllDemo_global.h"

class DLLDEMO_EXPORT IAbstractDllDemo
{
public:
    IAbstractDllDemo();
    virtual ~IAbstractDllDemo();

    virtual void print() = 0;
};

DLLDEMO_EXPORT IAbstractDllDemo* GetDllDemoInstance();

#endif // ABSTRACTDLLDEMO_H
