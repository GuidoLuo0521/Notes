#ifndef DLLDEMO_H
#define DLLDEMO_H

#include "abstractdlldemo.h"

class DllDemo : public IAbstractDllDemo
{
public:
    static DllDemo& GetInstance();

public:
    DllDemo();
    ~DllDemo();

    // AbstractDllDemo interface
public:
    void print() override;
};

#endif // DLLDEMO_H
