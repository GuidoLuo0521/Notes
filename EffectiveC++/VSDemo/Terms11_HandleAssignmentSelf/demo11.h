#pragma once

#include "../Common/common.h"

class Bitmap 
{
public:
	Bitmap() : a(0) {}
	Bitmap(const Bitmap& bmp)
		: a(0)
	{
		a = bmp.a;		// 类内函数，private 可以直接访问
	}

private:
	int a;
};

class Widget {
public:
	Widget() 
		: m_bitmap(nullptr) 
	{ 
		m_bitmap = new Bitmap; 
	}

	Widget(const Widget& w) 
		: m_bitmap(nullptr) 
	{
		m_bitmap = new Bitmap(*w.m_bitmap); 
	}

	Widget& operator= (const Widget& w);

#if DEBUG_SWAP
	
#if false
	template<class T = Widget>
	void swap(T & a)
	{
		Bitmap* itemp = this->m_bitmap;

		this->m_bitmap = a.m_bitmap;
		a.m_bitmap = itemp;
	}
#else
	void swap(Widget& a)
	{
		Bitmap* itemp = this->m_bitmap;

		this->m_bitmap = a.m_bitmap;
		a.m_bitmap = itemp;
	}


#endif

#endif

private:
	Bitmap* m_bitmap;

};
// 【常见普通版本】
#if DEBUG_NORMAL		
Widget& Widget::operator= (const Widget& w)
{
	delete m_bitmap;
	m_bitmap = nullptr;	// 最开始版本，赋值的时候就报错

	m_bitmap = new Bitmap(*w.m_bitmap);

	return *this;
}
// 【证同测试版本】
#elif DEBUG_SAMETEST 

Widget& Widget::operator= (const Widget& w)
{
	if (this == &w)
		return *this;

	delete m_bitmap;
	m_bitmap = nullptr;	// 最开始版本，赋值的时候就报错

	m_bitmap = new Bitmap(*w.m_bitmap);

	return *this;
}
// 【Swap版本】
#elif DEBUG_SWAP

Widget& Widget::operator= (const Widget& w)
{
	if (this == &w)
		return *this;

	Widget temp(w);
	swap(temp);

	return *this;
}


#endif
