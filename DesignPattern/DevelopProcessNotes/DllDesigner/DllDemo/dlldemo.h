#ifndef DLLDEMO_H
#define DLLDEMO_H

#include "abstractdlldemo.h"
#include "IInterfaceDemo.h"

class DllDemo : public IAbstractDllDemo, public IInterfaceDemo
{
public:
    static DllDemo& GetInstance();

public:
    DllDemo();
    ~DllDemo();

    // AbstractDllDemo interface
public:
    void print() override;
    void shape() override;
};

#endif // DLLDEMO_H
