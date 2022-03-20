#ifndef CONSTRUCTORTEST_H
#define CONSTRUCTORTEST_H

#include "common.h"

class Person
{
public:
    CONSTRUCTOR_DESTRUCTOR_DECL_IMPL(Person);

    string name;
};

class Student : public Person
{
public:
    CONSTRUCTOR_DESTRUCTOR_DECL_IMPL(Student)
};

class PrimarySchoolStudent : public Student
{
public:
    CONSTRUCTOR_DESTRUCTOR_DECL_IMPL(PrimarySchoolStudent)

};

void func(PrimarySchoolStudent student)
{
    std::cout << student.name << '\n';
};

#endif // CONSTRUCTORTEST_H
