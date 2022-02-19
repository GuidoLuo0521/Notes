#pragma once

#include <iostream>

using namespace std;

inline void PrintNewLine()
{
	cout << '\n';
}

inline void PrintSeparator()
{
	cout << "----------------------------------------";
	PrintNewLine();
}


inline void LogCall(const string& str)
{
	cout << str;
	PrintNewLine();
}