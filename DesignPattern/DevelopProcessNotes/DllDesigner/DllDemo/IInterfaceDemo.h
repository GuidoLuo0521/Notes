#ifndef IINTERFACEDEMO_H
#define IINTERFACEDEMO_H

#include "DllDemo_global.h"

class DLLDEMO_EXPORT IInterfaceDemo
{
public:
    IInterfaceDemo(){};
    virtual ~IInterfaceDemo(){};

    virtual void shape() = 0;
};



#endif // IINTERFACEDEMO_H
