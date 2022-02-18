#pragma once

#include "../Common/common.h"

class Bitmap 
{
public:
	Bitmap() : a(0) {}
	Bitmap(const Bitmap& bmp)
		: a(0)
	{
		a = bmp.a;		// ���ں�����private ����ֱ�ӷ���
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
// ��������ͨ�汾��
#if DEBUG_NORMAL		
Widget& Widget::operator= (const Widget& w)
{
	delete m_bitmap;
	m_bitmap = nullptr;	// �ʼ�汾����ֵ��ʱ��ͱ���

	m_bitmap = new Bitmap(*w.m_bitmap);

	return *this;
}
// ��֤ͬ���԰汾��
#elif DEBUG_SAMETEST 

Widget& Widget::operator= (const Widget& w)
{
	if (this == &w)
		return *this;

	delete m_bitmap;
	m_bitmap = nullptr;	// �ʼ�汾����ֵ��ʱ��ͱ���

	m_bitmap = new Bitmap(*w.m_bitmap);

	return *this;
}
// ��Swap�汾��
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
