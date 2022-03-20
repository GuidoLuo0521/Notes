#ifndef COMMON_H
#define COMMON_H


#include <string>
#include <iostream>
using namespace std;

#define COUT_FUNC_NAME cout << __FUNCTION__ << "\n"

//PRIVATE
#define CONSTRUCTOR_DECL_1(type, retType, name) \
    Q_PROPERTY(type name READ name CONSTANT)\
public:\
    Q_INVOKABLE retType name(){return m##name;}    \
protected:type m##name


#define CONSTRUCTOR_DESTRUCTOR_DECL_IMPL(retType) \
public:\
    retType(){ COUT_FUNC_NAME; }    \
    ~retType(){ COUT_FUNC_NAME; }


#endif // COMMON_H
