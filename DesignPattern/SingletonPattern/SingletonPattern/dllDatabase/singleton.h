#ifndef TEMPLATESINGLETON_H
#define TEMPLATESINGLETON_H

#include <QDebug>

template <typename T>
class CSingleton
{
private:
        static T* m_pInstance;

        CSingleton()         //构造函数为private
        {

        }

public:
       static T* getInstance()
       {
           return m_pInstance;
       }
};

template <typename T>
T*  CSingleton<T> :: m_pInstance = new T;



///
/// 单例模板
///
template<typename T>
class Singleton
{
public:
    static T& getInstance()
    {
        static T instance;
        return instance;
    }

    /*virtual*/ ~Singleton()
    {
        qDebug() << "~Singleton()"<< endl;
    }
protected:
    explicit Singleton()
    {

    }
};


#endif // TEMPLATESINGLETON_H
