#ifndef VIRTUALDESTRUCTORSTEST_H
#define VIRTUALDESTRUCTORSTEST_H

#include "Common.h"

#define VIRTUALDESTRUCTORTEST false

class A
{
public :
    A() {
        std::cout << __FUNCTION__ ;
        PrintNewLine();
    }
#if VIRTUALDESTRUCTORTEST
    virtual ~A() {
        std::cout << __FUNCTION__;
        PrintNewLine();
    }
#else
    ~A() {
        std::cout << __FUNCTION__;
        PrintNewLine();
    }
#endif

};

class B : public A
{
public:
    B() {
        std::cout << __FUNCTION__;
        PrintNewLine();
    }
    ~B() {
        std::cout << __FUNCTION__;
        PrintNewLine();
    }

private:

};


#endif // VIRTUALDESTRUCTORSTEST_H
