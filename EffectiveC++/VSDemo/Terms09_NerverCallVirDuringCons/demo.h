#pragma once

#include "../Common/common.h"

class A {
public:
	A()
	{
		//print();
	}
	virtual ~A()
	{

	}
	

	virtual void print()
	{
		cout << "A::" << __FUNCTION__;
		PrintNewLine();
	}
};

class B : public A
{
public:
	B()
	{
		print();
	}
	virtual ~B()
	{

	}

	virtual void print()
	{
		cout << "B::" << __FUNCTION__;
		PrintNewLine();
	}
};