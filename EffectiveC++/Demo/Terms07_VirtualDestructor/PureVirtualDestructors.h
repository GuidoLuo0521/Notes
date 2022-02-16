#ifndef PUREVIRTUALDESTRUCTORS_H
#define PUREVIRTUALDESTRUCTORS_H

#include "Common.h"

// pure virtual
class VA
{
public:
    virtual ~VA() = 0;
};

VA::~VA(){
    std::cout << __FUNCTION__ ;
    PrintNewLine();
}


class VB : public VA
{
public:
    VB() {
        std::cout << __FUNCTION__ ;
        PrintNewLine();
    }
    ~VB() {
        std::cout << __FUNCTION__ ;
        PrintNewLine();
    }
};

#endif // PUREVIRTUALDESTRUCTORS_H
