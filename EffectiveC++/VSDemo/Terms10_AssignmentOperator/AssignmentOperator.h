#pragma once
#include "../Common/common.h"

class A {
public:
	A() : a(++count){}

	A& operator= (const A& a)
	{
		this->a = a.a;
		return *this;
	}

	void print(const string& flag)
	{
		cout << __FUNCTION__ << " " << flag << " " << a;
		PrintNewLine();
	}
private:
	int a;

	static int count;
};

int A::count = 0;