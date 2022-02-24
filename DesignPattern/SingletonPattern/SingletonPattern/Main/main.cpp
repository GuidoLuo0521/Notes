#include <QCoreApplication>
#include <QDebug>

#include "../dllTest0/testinfo.h"
#include "../dllTest1/dlltest1.h"

#include "common.h"
#include "eagersingleton.h"
#include "lazysingleton.h"
#include "testthread.h"

#include <iostream>

#include "../dllTest0/singletontest0.h"
#include "../dllTest1/singletontest1.h"

// 【基础版本演示部分】
void ShowBaseVersion()
{
    sg_DllTest1.printName();

    DllTest1 dll1;

    sg_TestInfo.setName("123");
    sg_TestInfo.printName();

    dll1.setTestName("25");
    sg_TestInfo.printName();
}

// 【懒汉模式版本演示部分】
void ShowLazyModel()
{
    ThreadLazy lazy1;
    ThreadLazy lazy2;

    lazy1.start();
    lazy2.start();


    lazy1.wait();
    lazy2.wait();

     //LazySingleton::instance().printTest();
}

// 【饿汉模式指针版本演示部分】
void ShowEagerPtr()
{
    ThreadEagerPtr eager1;
    ThreadEagerPtr eager2;
    eager1.start();
    eager2.start();

    eager2.wait();
    eager2.wait();
//    EagerSingleton::instance()->printTest();
}

// 【饿汉模式引用版本演示部分】
void ShowEagerRef()
{
    ThreadEagerRef eager1;
    ThreadEagerRef eager2;
    eager1.start();
    eager2.start();

    eager2.wait();
    eager2.wait();
}

// 【寄存器演示】
void ShowRegister()
{
    int const tmp = 100;	//定义常量tmp tmp不能修改

    // const 出现在 * 的左边，表示被指物是常亮
    // const 出现在 * 的右边，表示指针自身是常量
    int const* p = &tmp;	//不能通过指针修改指向的值
    int* const q = const_cast<int*>(p); //去常属性 可以通过指针修改指向的内容
    *q = 200;
    std::cout << "tmp:" << tmp << std::endl
              << "*p:"  << *p << std::endl
              << "*q:"  << *q << std::endl;	//打印变量的值
    std::cout << &tmp << std::endl << p << std::endl << q << std::endl;	//打印变量地址

}

// 【演示单例模版跨 dll】
void ShowTemplateSingleton()
{
    SingletonTest0 sig0;
    sig0.printTest();
    SingletonTest1 sig1;
    sig1.printTest();
}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    qDebug() << "\nhello world";



    //ShowEagerRef();

    ShowTemplateSingleton();


    return a.exec();
}
