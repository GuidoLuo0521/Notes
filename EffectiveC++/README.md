> 记录阅读过程中的摘录和理解

# 条款1  视C++为一个语言联邦

今天的C++是一个 **多重范型编程语言** ，一个同时支持 **过程形式，面向对象形式，函数形式，泛型形式，元编程形式** 的语言

过多的支持导致了用法的不确定性，所有的路都可以走通，怎么选择就是最大的问题了。如何选择才最适合。

最简单的方法就是，将C++视为一个 **由相关语言组成的联邦而非单一的语言，在其某个次语言中，各种守则与通例都倾向简单，直观易懂，并且容易记住，当从一个次语言移往另一个次语言，守则可能改变**



## C++ 的次语言分类

* C
* Object-Oriented C++
* Template c++
* STL

## C

说到底，C++ 仍然是以C为基础

> 区块： `｛｝`包括起来
>
> 语句：`；`结束
>
> 预处理器： `#define`
>
> 内置数据类型： `int`，`bool`
>
> 数组：` [ ]` 
>
> 指针： `* `
>
> 。。。

上面这一部分，都是来自 C，所以很多时候，C++的问题不过就是高级一点的 C 的解法。

所以，当用 C 的成分来工作的时候，高效编程守则就映照出 **C 语言的局限，没有模板，没有异常，没有重载...**



## Object-Oriented C++  

面向对象

这部分就是 C with class 所诉求的，classes（构造函数和析构函数）

> 封装：将数据成员隐藏
>
> 继承：子类获取父类的方法，成员等
>
> 多态：不同数据类型的实体提供统一的接口，
>
> virtual函数（动态绑定：就是运行到的时候，才指向）
>
> 。。。

这一部分，是面向对象设计之古典守则在C++上的最直接实施。



## Template C++

C++ 的泛型编程

> 发明一种语言机制，能够帮助实现一个通用的标准容器库。所谓通用的标准容器库，就是要能够做到，比如用一个[List](https://baike.baidu.com/item/List/4825101)类存放所有可能类型的对象这样的事；泛型编程让你编写完全一般化并可重复使用的算法，其效率与针对某特定数据类型而设计的算法相同。泛型即是指具有在多种[数据类型](https://baike.baidu.com/item/数据类型/10997964)上皆可操作的含义，与模板有些相似。`STL`巨大，而且可以扩充，它包含很多计算机基本算法和[数据结构](https://baike.baidu.com/item/数据结构/1450)，而且将算法与数据结构完全分离，其中算法是泛型的，不与任何特定数据结构或对象类型系在一起。

Template 的相关考虑与设计已经弥漫整个 C++ ,良好的守则中，唯 template 适用的条款并不罕见（条款 46）。

由于 Template 的威力强大，他们带来崭新的编程范型，也就是（`TMP`，模板元编程），`TMP`相关的规则很少与C++主流编程互相影响。



## `STL`

`STL`是一个 ` template ` 程序库

他对 容器（ containers），迭代器（iterators），算法（algorithms）以及函数对象（function objects）的约束有极佳的紧密配合与协调，然而 template 及程序库也可以用其他的想法构建出来。`STL`有自己的办事方式，所以要用他的时候，就自己遵守它的规定。、

## 总结

所以，当在上面四个类型切换的时候，要变换策略

* 内置类型（ **C**）值传递比引用传递更高效，
* 从 **C**到 **Object-Oriented C++**的时候，由于用户自定义构造函数和析构函数的存在，`const` 的引用传递（`pass by reference to const` ）更好，运用 Template C++ 的时候尤其如此，因为到时候，不知道处理的是什么类型。
* 当跨入 `STL`的时候，你又会了解到，迭代器和函数对象都是在 C 指针上塑造出来的，所以，对 `STL`的迭代器和函数对象而言，旧式的 C `pass by value`守则再次适用。

<font color=red>**所以，守则就是在这四个类型上面切换策略。**</font>





# 条款2 尽量以 `const`，`enum`，` inline`替换 `#define`

这个条款或许改成  **宁可以编译器替换预处理器**

因为， `#define` 不被视为语言的一部分，这正是问题所在。所以，当定义一个宏

~~~c++
#define ASPECT_RATIO 1.63
~~~

 记号名称 `ASPECT_RATIO` 也许从未被编译器看见；也许在编译器开始处理源代码之前它就被预处理器移走了。于是，`ASPECT_RATIO` 可能就没有进入记号表`sysbol table`。于是，在运用此常量，但是又获得一个编译错误信息的时候，就可能会带来疑惑，因为这错误提到的是 `1.63` 而非 `ASPECT_RATIO` ，但是又对此记号毫无概念，那么查找的时候就会很麻烦，从而浪费时间。

​	解决方法以一个常亮替换上面的宏

~~~c++
const double ASpectRation = 1.63;
~~~

所以，作为一个常量，那就肯迪会被记号表看到。



## **以常量替换 `#define` 的两种特殊情况**

* 定义常量指针

  > 因为常量指针通常放在头文件中，所以如果要在头文件中写常量指针，最好写两次
  >
  > ~~~c++
  > const char* const author = "guido";
  > // 更好的是
  > const std::string author = "guido";
  > ~~~
  >
  > 

* `class` 专属常量

  > 要将常量的作用域（scope）限制在`class`之中，那必须让它成为 `class` 的一个成员
  >
  > ~~~c++
  > // .h
  > class GamePlayer
  > {
  >     private:
  >     static const int NumTurns = 5; // 常量声明，而非定义，就是说明，此时还没有给内存空间。
  >     int m_scores[NumTurns]; // 使用常量
  > }
  > //.cpp
  > const int GamPlayer::NumTurns;	// 常量定义，就是要内存空间了。因为声明的时候有值了，所以，此时就可以不设初值了
  > ~~~
  >
  > ！！！ 但是，没办利用 `#define` 为 `class` 创建一个专属常量，因为 `#define` 不重视作用域（scope）
  >
  > 一旦被定义，他就在其后的编译过程中有效（除非 `#undef`），所以，`#define` 不具备封装性。而 `const` 是可以被封装的。



## 需要在 `class` 编译期间知道一个 `class` 常量值怎么办

因为有的编译器不支持 `in class 初值设定`，那么上面的定义 `static const int NumTurns = 5;` 就获取不了这个值了。。

也有替换方式，使用 `enum`

~~~c++
// .h
class GamePlayer
{
    private:
    enum { NumTurns = 5 };	// the enum hack
    int m_scores[NumTurns]; // 使用常量
}
//.cpp
const int GamPlayer::NumTurns;	// 常量定义，就是要内存空间了。因为声明的时候有值了，所以，此时就可以不设初值了
~~~



## `enum hack`

**好处** 

* 不能对 `enum` 常量值取地址，所以，别人不能更改，如果使用 pointer 或 reference，那就可能被别人使用取地址，更换值。造成错误
* 实用主义，其他别人用到了，所以必须认识它。
* 是 `template metaprogramming`（模板元编程）的基础技术（条款48）



## 宏函数

虽然，宏函数没有调用开销，但是，带参数的宏错误的可能性却很大

~~~c++
// 以 a 和 b 的较大值调用 f
#define CALL_WITH_MAX(a, b) f((a) > (b) ? (a) : (b))

// 情况
int a = 5, b = 0;
CALL_WITH_MAX( ++a, b); 			// a 被累加两次
CALL_WITH_MAX( ++a, b + 10); 		// a 被累加一次
~~~

所以，上面的情况就可能出错，那么更好的替换的情况就是， **使用模板函数来替换** 就可以获得同等的效率和安全性

`template inline` （条款30）

~~~c++
template<typename T>
inline void callWithMax(const T& a, const T& b)
{
    f( a > b ? a : b );
}
~~~

有了 `consts`，`enums`和 `inlines`，我们对预处理器（特别是`#define`）的需求降低了，但并非完全消除。

`#include ` 任然是必需品，而`#indef / #ifndef`也继续扮演 **控制编译** 的重要角色



## 总结

* 对于单纯常量，最好使用 `const`对象或 `enums` 替换 `#defines`
* 对于形似函数的宏`macros`，最好改用 `inline`函数替换 `#define`





# 条款3	尽可能使用`const`

`const` 允许你指定一个语义约束（即，指定一个不该改动的对象），而编译器会强制实施这项约束。它允许你告诉编译器和其他程序员，某值应该保持不变。只要某值保持不变是事实，那么，就应该明确的说出来，因为，说出来就可以获得编译器的帮助，确保这条约束不被违反。

`const`可以修饰的东西太多了

*  指针
* 数值
* 函数
* 。。。

虽然使用的很多，但是并不高深。法则如下

* 如果关键字 `const` 出现在星号的左边，表示被指物是常量
* 如果关键字 `const` 出现在星号的右边，则表示指针自身是常量。（这就话就是，出现在右边的只有指针咯，函数也算指针~~）
* 如果两边都出现，那就是物和指针都是常量

> 如果物是常量，有两种写法
>
> ~~~c++
> void f1( const Widget* pw);		// f1 获得一个指针，指向一个常量的 Widget 对象
> void f2( Widget const * pw);	// f2 一样
> ~~~
>
> 那就是看 `const` 后面跟的是什么
>
> ~~~c++
> 第一个 const 后面是 Widget ;
> 第二个 const 后面是 *pw;			都表示一个对象
> 还是第一条法则，如果关键字 `const` 出现在星号的左边，表示被指物是常量
> ~~~



## `STL` 迭代器

`stl` 迭代器系列，就是以指针为根据塑造出来的，所以，迭代器的作用就像 `T*`指针。

声明迭代器为 `const` 就像声明指针为 `const` 一样（即，声明一个 `T* const `）, 表明，这个指针不能更改，但是，指针指向的对象可以更改。

如果，希望迭代器所指的东西不可被改动（即：一个 `const T*` 指针），那就可以用 `const_iterator`

~~~c++
std::vector<int> vec;
const std::vector<int>::iterator iter = vec.begin();	// 声明迭代器为 const ，指针不能更改，指向内容可以更改
*iter = 10;		// 正确
++iter;			// 错误

std::vector<int>::const_iterator citer = vec.begin(); // 声明一个常量迭代器，说明，迭代器可更改，但是指向内容不可更改
*citer = 10;	// 错误	
++citer;		// 正确
~~~



## `const` 成员函数

两个重要的理由

* 使得 `class` 接口比较容易理解，得知哪个函数可以改变内容，哪个函数不可以改变内容。
* 使操作 `const` 对象成为可能。

**如果两个成员函数只是常量性不同，是可以被重载的，这也是c++的一大特性。**

~~~c++
class TextBlock {
    public : 
	    const char& operator [] (std::size_t position) const { return text[position]; }  // 重载 [] 为一个 const 对象	
    	char& operator [] (std::size_t position) const { return text[position]; }		// 重载 [] 为一个非 const 对象 ( non-const ) 
    private:
    	std::string text;
}

// 例子 1
fun()
{
    TextBlock ta("Hello");
    std::cout << ta[0];	 	// 调用的是 non-const
    ta[0] = 'j';		// 可以，因为返回的是 non-const
    
    const TextBlock tb("World");
    std::cout << tb[0];		// 调用的是 const
    tb[0] = 'j';		// 错误，因为返回的是 const
}
~~~

最后写一个，可以在 `const` 成员函数内部更改值的方式

~~~c++
// .h
class TextBlock {
    public : 
	    const char& operator [] (std::size_t position) const { return text[position]; }  // 重载 [] 为一个 const 对象	
    	char& operator [] (std::size_t position) const { return text[position]; }		// 重载 [] 为一个非 const 对象 ( non-const ) 
    
    	std::size_t length() const;
    private:
    	std::string text;
    	mutable std::size_t textLength;		// 这个修饰的成员变量，总能在 const 函数内被修改
}

// .cpp
std::size_t length() const
{
    // 这里只做演示，真实情况自己判定，仅仅为了演示关键字  mutable 
    textLength = 10;
    return textLength;
}
~~~

感觉后面的对实际开发的意义就不大了~~，就不写了，下面总结最后一条会写到。

## 总结

* 尽可能使用 `const`来帮助编译器侦测出错误， `const ` 可被施加于任何作用域内的对象，函数参数，函数返回类型，成员函数本体。
* 当 `const`和 `non-const `成员函数有着实质等价的实现的时候，令 `non-const` 版本调用 `const` 版本可避免代码重复。

