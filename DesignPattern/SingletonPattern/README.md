# 单例模式

## 动机

对于一个软件系统，一个实例就够了，不需要多个的时候就可以用 【单例】。开多了会浪费资源，完全没有必要。

* 数据库
* 任务栏管理器
* 文件系统
* 数据池





## 基础版本

~~~c++
DLLTEST0_EXPORT extern TestInfo sg_TestInfo;
~~~

好处：简单方便，

坏处：对多项目，多线程的兼容性不好。

*  C++ 对于定义于不同编译单元内的 `non-local static` 对象的初始化顺序并没有明确的规定。可能导致错误。

> 实例代码
>
> ~~~c++
> // dll0
> DLLTEST0_EXPORT extern TestInfo sg_TestInfo;
> // dll1
> DllTest1 sg_DllTest1 = DllTest1(sg_TestInfo);
> ~~~
>
> 

·

## 懒汉模式

懒加载，就是在用户使用的时候才加载，同界面一个道理，好比一个 widget，如果下面有10个tab，那么进页面的时候就加载一个，不用一次加载10个。

### `V1.0` 基础版本

* 线程不安全

  > 原因：`cpu` 分配时间片

~~~c++
class LazySingleton : public TestBase
{
public:
    static LazySingleton* instance();
private:
    LazySingleton();

private:
    static LazySingleton * m_instance;
};

//cpp
LazySingleton * LazySingleton::m_instance;

// 多线程错误
LazySingleton* LazySingleton::instance()
{
    if(nullptr == m_instance)
    {	
        // 切换线程
        m_instance = new LazySingleton;
    }

    TEST_MSG("LazySingleton address : ", m_instance);
    return m_instance;
}

~~~

### `V2.0`  一重加锁

~~~c++

QMutex g_mutex;
LazySingleton* LazySingleton::instance()
{
    QMutexLocker locker(&g_mutex);
    if(nullptr == m_instance)
    {
        m_instance = new LazySingleton;
    }

    TEST_MSG("LazySingleton address : ", m_instance);
    return m_instance;
}
~~~

* 缺点：浪费资源

### `V3.0` 双重锁定

* 不浪费过多资源，代码过多，麻烦
* 看饿汉模式

~~~c++
QMutex g_mutex;
LazySingleton* LazySingleton::instance()
{
    if(nullptr == m_instance)
    {
        QMutexLocker locker(&g_mutex);
        if(nullptr == m_instance)
        {
            m_instance = new LazySingleton;
        }
    }

    TEST_MSG("LazySingleton address : ", m_instance);
    return m_instance;
}

~~~



## 饿汉模式

程序建立的时候就创建，分配到全局变量区

* 线层安全（[c++11](https://oomake.com/question/326422)），原因，**C++ 规定对于 `static` 对象，在遇到他的第一次进行初始化**，其他的并发将等待初始化完成。
* 

### `v1.0` 返回引用

~~~c++
class EagerSingleton : public TestBase
{
public:
    static EagerSingleton& instance();

private:
    EagerSingleton();
   
	static EagerSingleton m_instance;
};

// 
EagerSingleton EagerSingleton::m_instance;



EagerSingleton& EagerSingleton::instance()
{
     static EagerSingleton m_instance;
    
    // c++11 安全 03 不安全
    TEST_MSG(" EagerSingleton address : ", &m_instance);
    return m_instance;
}

~~~



### `V2.0` 返回 指针

* 别人给删除了

~~~C++
EagerSingleton* EagerSingleton::instance()
{
    TEST_MSG(" EagerSingleton address : ", &m_instance);
    return &m_instance;
}
~~~




## 模板模式

* 存在 `dll` 不同的问题，导致并不是一个单例

~~~c++
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

~~~







