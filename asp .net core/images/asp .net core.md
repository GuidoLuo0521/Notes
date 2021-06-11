# asp .net core

## 依赖注入

 依赖注入是一个过程，就是当一个类需要调用另一个类来完成某项任务的时候，在调用类里面不要去new被调用的类的对象，而是通过注入的方式来获取这样一个对象。具体的实现就是在调用类里面有一个被调用类的接口，然后通过调用接口的函数来完成任务。比如A调用B，而B实现了接口C，那么在A里面用C定义一个变量D，这个变量的实例不在A里面创建，而是通过A的上下文来获取。这样做的好处就是将类A和B分开了，他们之间靠接口C来联系，从而实现对接口编程。 



## Razor 

- Razor 是一种将基于服务器的代码添加到网页中的标记语法
- Razor 具有传统 ASP.NET 标记的功能，但更容易使用并且更容易学习
- Razor 是一种服务器端标记语法，与 ASP 和 PHP 很像
- Razor 支持 C# 和 Visual Basic 编程语言

~~~C#
<!DOCTYPE html>

<html lang="en">
<head>
<meta charset="utf-8" />
<title>Web Pages Demo</title>
</head>
    
<body>
	<h1>Hello Web Pages</h1>
	<p>The time is @DateTime.Now</p>
</body>
</html>
~~~









# 梁桐铭教程

 https://www.bilibili.com/video/av48164112?spm_id_from=333.788.b_765f64657363.1 

## 项目文件

### launchSettings.json

* 本地开发的时候使用的配置文件

### appsettings.json

* 运行时的配置文件，采用依赖注入的方式获取

获取值的过程

* 设置配置表的值
* 在相应的类构造函数中增加IConfiguration类型参数  获取配置文件的信息 (增加到 IConfiguration _con中  )   这里就是依赖注入的方式，在main函数的时候调用的 CreateDefultBuilder()中进行配置
  * CreateDefultBuilder()
    * 设置web服务器
    * 加载主机和APP之间的配置信息
    * 配置日志记录
* 使用配置表的值   _con["key"];

获取值的顺序

* appsettings.json  运行配置文件
* appsettings.{Enviroment}.json  不同环境的开发环境不同
* user secrets  用户机密  项目文件右键 管理用户机密
* Enviroment variables 环境变量
* command-line arguments 命令行参数

### project.csproj

双击项目出现

项目的一些配置

比如：采用的托管方式，依赖的包

#### 托管方式：

<AspNetCoreHostingModes>  ** </AspNetCoreHostingModes>

进程内（InProcess），进程外(OutOfProcess)

##### 进程内：

![1595093723925](C:\Users\pg\OneDrive\学习笔记\asp .net core\images\1595093723925-1604849529098.png)

* 采用IIS工作进程，w3wp.exe
* 只有一个Web服务器
* 进程内托管的性能比进程外要高 

##### 进程外：

将web请求转发到后端的asp.net core中，整个APP是在kestrel中运行

![1595093887367](images\1595093887367-1604849530898.png)

* 两个Web服务器
  * 内部服务器-->Kestrel
  * 外部服务器-->IIS,NgInx,Apache
* 用于托管的进程是 dotnet.exe（cmd那个）



## 中间件（Middleware）

就是Request和Responce中间的过程所需要的部件。再startup::configure()中添加 ，app.***();

* 可同时被访问和请求
* 处理请求后将请求传递给下一个中间件或者不传递给下一个，当不传递给下一个的时候就叫终端中间件          （ terminal middleware ）这样就节约时间等。
* 可处理传出响应，比如记录时间等。
* 中间件是按添加的顺序来访问的（添加到**管道**中的顺序）
* 中间件调用 next()进入下一个中间件

### 微软默认提供

![1595129373074](images\1595129373074-1604849533024.png)





~~~C#
        public void Configure(IApplicationBuilder app, IWebHostEnvironment env)
        {
            if (env.IsDevelopment())
            {
                app.UseDeveloperExceptionPage();
            }

            app.Use(async (context, next) =>
            {
                context.Response.ContentType = "text/plain;charset=utf-8";

                await context.Response.WriteAsync("你好 World \n");
                await next();

            });

            app.Run(async context => await context.Response.WriteAsync("我好 World"));

        }

// 
~~~





## 静态文件

默认的目录是 wwwroot

~~~C#
            /// 修改默认选项 自定义默认
            //DefaultFilesOptions defaultFiles = new DefaultFilesOptions();
            //defaultFiles.DefaultFileNames.Clear();
            //defaultFiles.DefaultFileNames.Add("Guido.html");

            //// 添加默认文件中间件 
			// 放置在 UseStaticFiles()才行
            // 默认支持文件
            // index.html   index.htm   default.htm  default.html
            //app.UseDefaultFiles(defaultFiles);             

            //// 添加静态文件中间件
            //app.UseStaticFiles();

            // 自定义默认
            // file server 相当于再封装一层 DefaultFilesOptions
            FileServerOptions fileServerOptions = new FileServerOptions();
            fileServerOptions.DefaultFilesOptions.DefaultFileNames.Clear();
            fileServerOptions.DefaultFilesOptions.DefaultFileNames.Add("Guido.html");
            app.UseFileServer(fileServerOptions);

            // 微软准备的中间件
            // app.use***();

~~~



### 1、静态文件中间件

* 默认情况不支持，需要添加 

  ~~~C#
  public void Configure(IApplicationBuilder app, IWebHostEnvironment env)
  {
      // 仅提供wwwroot中的静态文件
  	app.UseStaticFiles();    
  }
  ~~~

* 静态文件的默认目录是**wwwroot**文件夹，此文件夹在项目文件的根目录下面

  ~~~C#
  // 将文件复制到wwwroot内，为了从浏览器访问，可将url设置为
  https://localhost:44393/images/img.jpg
  ~~~


![1604849668357](images\1604849668357.png)

### 2、默认文件

访问程序地址的时候显示的文件内容

![1604849391794](images\1604849391794-1604849537497.png)

为了提供默认页面，需要在程序的请求管道中增加

~~~C#
public void Configure(IApplicationBuilder app, IWebHostEnvironment env)
{
	app.UseDefaultFiles();
}
~~~

必须在使用**UseStaticFiles()**之前使用**UseDefaultFiles()**来提供默认文件。

因为**UseDefaultFiles()**是一个url重写器，实际上并不提供文件，只是将url重写到默认文件，然后再由静态文件中间件提供。所以，地址栏显示的还是根节点的url，而不是重写的url。

默认文件的顺序

* index.htm
* index.html
* default.htm
* default.html

新增的default.html都需要放入wwwroot文件夹的根目录中，否则无法运行。



### 3、自定义的默认文件

如果要使用其他文件作为默认文件，可以这样写。

![1604850519462](images/1604850519462.png)



~~~C#
DefaultFilesOptions Class
Definition
Namespace:Microsoft.AspNetCore.Builder
Assembly:Microsoft.AspNetCore.StaticFiles.dll
    
Options for selecting default file names.

public class DefaultFilesOptions : Microsoft.AspNetCore.StaticFiles.Infrastructure.SharedOptionsBase
~~~



### 4、UseFileServer中间件

​	UserFileServer() 结合了 UseStaticFiles()、UseDefaultFiles()、UseDirectoryBrowser()中间件的功能，UseDirectoryBrowser()支持目录浏览，并允许用户查看指定的目录中的文件。所以可用UserFileServer() 来替代UseStaticFiles()、UseDefaultFiles()，下面为代码。

![1604851397019](images/1604851397019.png)

！！！注意！！！

​	凡是开发.netcore项目，我们都应该将中间件添加到应用程序的请求管道中进行开发。大多数情况下，中间件都是以Use开头的扩展方法

~~~C#
UseDeveloperExceptionPage();
UseDefaultFiles();
UseStaticFiles();
UseFileServer();   
~~~



### 5、小结

* Asp .NetCore不支持静态文件
* 默认的静态文件文件夹为 wwwroot
* 要使用静态文件，必须使用 UseStaticFiles()中间件
* 要定义默认文件，必须使用UseDefaultFiles()中间件
* 默认的文件如下
  * Index.htm
  * Index.html
  * default.htm
  * default.html
* 必须在UseStaticFiles()之前注册UseDefaultFiles()
* UserFileServer() 结合了 UseStaticFiles()、UseDefaultFiles()、UseDirectoryBrowser()中间件的功能









## 开发者异常页面

### 1、直接抛出异常

        public void Configure(IApplicationBuilder app, IWebHostEnvironment env)
        {
            if (env.IsDevelopment())
            {
            	// **
                app.UseDeveloperExceptionPage();
            }
            app.Run(async context =>{ throw new Exception("发生了一些错误。");});
        }
### 2、自定义异常

~~~C#
if (env.IsDevelopment())
{
	// 在错误页面显示的错误上方和下方的行数
	// 尽早提前注入
	DeveloperExceptionPageOptions pageOptions = new DeveloperExceptionPageOptions();
	pageOptions.SourceCodeLineCount = 10;	
	app.UseDeveloperExceptionPage(pageOptions);
}
~~~

！！！在注册的后面显示异常，所以尽早的加入这个中间件

### 3、配置环境变量

一般有以下几种软件开发环境

* 开发环境（Development）
* 演示（模拟，临时）环境（Staging）
* 生产环境（Producting）

访问 **ASPNETCORE_ENVIRONMENT**的值

~~~C#
 public void Configure(IApplicationBuilder app, IWebHostEnvironment env)
 {
  	env.EnvironmentName; 
 }
~~~



## MVC控制结构

模型（Model），视图（View）,控制器（Controller）

![](images/1605022848535.png)

### MVC流程

1、请求到达服务器，MVC设计模式下的Controller会接受请求并且处理它。

2、Controller会访问Model，该模型是一个类文件，会进行数据的展示。

3、除了数据本身，Model还包含从底层数据源（如数据库）查询数据后的代码处理逻辑。

4、访问Model完成后，Controller还会继续选择View，并将Model对象，传递给View。

5、View仅仅负责呈现Model的数据。

6、View会根据Model数据所生成的HTML页面代码以显示Model数据，简单来说就是Controller提供给View学生数据。

7、生成的HTML页面通过网络发送给请求的用户。



#### Model

**包含一组数据的类和管理该数据的逻辑信息**

~~~C#
// 数据是 student 逻辑是StudentRepository
~~~

![1605021875106](images/1605021875106.png)



#### View

**大多数时候只是显示Controller提供给他的Model数据的逻辑，可以将View视为Html模板。**

假如，我们希望在Html表格中显示Student数据，则可以将View和Student对象放在一起。Student对象是将学生数据传递给View的模型。

View的唯一作用是将学生数据显示在Html表格中。

![1605022461438](images/1605022461438.png)

#### Controller

**处理Http请求，调用模型，选择View呈现。**



### 安装MVC

空模板项目中没有添加MVC，所以需要自己添加

~~~c#
// 添加Mvc服务到依赖注入容器中
public void ConfigureServices(IServiceCollection services)
{
	services.AddMvc(a => a.EnableEndpointRouting = false);
}

// 添加MVC默认路由
public void Configure(IApplicationBuilder app, IWebHostEnvironment env)
{
    // 默认中间件
    app.UseStaticFiles();

    app.UseMvcWithDefaultRoute();
}
~~~

这里将UseStaticFiles();放在 UseMvcWithDefaultRoute()前面，就是为了让只在请求 文件的时候就直接返回了，不走管道后面的中间件，节约时间。

跳转到UseMvcWithDefaultRoute()接口，摘要中要求 增加默认控制器模板

~~~C#
pipeline with a default route named 'default' and the following template: '{controller=Home}/{action=Index}/{id?}'
~~~

![1605108749123](images/1605108749123.png)



从 ASP.NET Core 2.x 到 ASP.NET Core 3.0

AddMvc() 有变化

2.x中，AddMvc()接口中增加的服务比较多

3.x中，AddMvc()中调用的接口又分类了

这个看源码去

之说结论，在3.x中噶成这样就行了

![1605110632387](images/1605110632387.png)





### 小结

Mvc：用于实现应用程序的用户界面层的架构思想

Model：包含一组数据的二类和管理该数据的逻辑信息。

View：包含显示逻辑，用于显示Controller提供给Model的数据。

Controller：处理Http请求，调用模型，选择View呈现。



## 依赖注入

```c#
// Student.cs
public class Student
{
    public Student(int id, string name)
    {
        m_nId = id;
        m_strName = name;
    }

    public int m_nId { get; set; }
    public string m_strName { get; set; }
}

// IStudentRepository.cs
public interface IStudentRepository
{
    Student GetStudent(int id);
    void SetStudent(Student stu);
}

// MockStudentRepository.cs
public class MockStudentRepository : IStudentRepository
{
    List<Student> students = new List<Student>();

    public MockStudentRepository()
    {
        students.Add(new Student(0, "张三"));
        students.Add(new Student(0, "李四"));
        students.Add(new Student(0, "杨琳"));
        students.Add(new Student(0, "张印"));
        students.Add(new Student(0, "嘴巴"));
    }


    public Student GetStudent(int id)
    {
        return  students.Find((Student stu) => stu.m_nId == id);
    }

    public void SetStudent(Student stu)
    {
        students.Add(stu);
    }
}

// Startup.cs
public void ConfigureServices(IServiceCollection services)
{
    //services.AddMvc(a => a.EnableEndpointRouting = false);
    services.AddControllersWithViews(a => a.EnableEndpointRouting = false);
    
    // 增加依赖注入
    // 添加当前web接口获取学生的具体实现的类
    services.AddSingleton<IStudentRepository, MockStudentRepository>();
}

```
### 添加服务

三种添加服务的接口

* AddSingleton();

  创建一个Singleton服务，首次请求时会创建，后续请求都采用相同的实例。每个应用程序只创建一次并且在程序的整个生命周期只用他。

* AddTransient();

  暂时性的，每次请求都创建一个。

* AddScoped();

  每个请求都创建一个Scoped服务，单个客户端的请求相同，多个客户端请求各不同

### 小结

* 降低耦合









## 控制器中将数据传入视图

* 使用ViewData
* 使用ViewBag
* 强类型视图    **首选**

### 路径

        public ViewResult Details()
        {
            Student student = _studentRepository.GetStudent(0);
            ViewData["PageTitle"] = "学生";
            ViewData["Student"] = student;
    
            // object
            //return View(student);
    
            // viewName; 
            // test/home/test.cshtml
            // return View("Test");
    
            // view path (abs)
            // return View("~/views/home/Test.cshtml");
            // return View("views/home/Test.cshtml");
            // return View("/views/home/Test.cshtml");
            
            // 相对路径
            // home 文件夹下的 test.cshtml
            return View("../home/Test");
        }
![ ](images/1605793509234.png)

### ViewData

* 弱类型的字典对象
* 使用string类型的键值，存储和查询ViewData字典中的数据
* 运行时动态解析
* 编译时无类型检查

~~~ C#
// controller 中
            Student student = _studentRepository.GetStudent(1);
            ViewData["PageTitle"] = "学生";
            ViewData["Student"] = student;
~~~

~~~ html
// view中
@using ASPNETCore2Start.Model;
<body>
    <h3>@ViewData["PageTitle"]</h3>
    @{ var student = ViewData["Student"] as Student;}
    <div> 学号：@student._ID </div>
    <div> 姓名：@student._Name </div>
    <div> 年龄：@student._Age </div>
</body>
~~~

![1595174306510](C:\Users\pg\AppData\Roaming\Typora\typora-user-images\1595174306510.png)

​																            请求结果



### ViewBag

* 封装了一次ViewData，使用动态类型(dynamic)

* 弱类型视图
* 运行时解析
* 不提供编译时类型检查和智能提示

~~~ C#
  // controller 中
			Student student = _studentRepository.GetStudent(2);
            ViewBag.PageTitle = "学生详情";
            ViewBag.Student = student;
~~~

~~~ html
// view 中
@model ASPNETCore2Start.Model;
<body>
    <h3>@ViewBag.PageTitle</h3>
    <div> 学号：@ViewBag.Student._ID </div>
    <div> 姓名：@ViewBag.Student._Name </div>
    <div> 年龄：@ViewBag.Student._Age </div>
</body>
~~~



### 强类型视图

**!!!! 首选方案：从控制器到视图**

控制器部分：在控制器中将模型对象传递给View()方法

视图部分：使用 @model指令在视图中指定模型类型，比如下面，就是使用命名空间为 MockSchoolManagement.Models中的对象，将Student对象作为模型。

​	注意：在**指令 @model**中，m是小写，要访问模型对象属性，要使用**@Model访问**

~~~C#
//  controller部分代码
public ViewResult Details()
{
	Student model = _StudentRepository.GetStudent(0);
    ViewBag.PageTitle = "学生详情";
    
    return View(model);
}
// view代码
@model MockSchoolManagement.Models.Student
<html>
    <body>
    	<h2>@ViewBag.PageTitle</h2>
    	<h3>@Model._Name</h3>
    	<h3>@Model._Email</h3>
    </body>
</html>    
~~~

####  PageTitle用强类型

新建一个ViewMode 视图模型 作为传输数据的封装类  ,

DTO：data transform object  传输数据对象

~~~ C#
// controller中
            // 复杂强类型
            HomeDetailsViewModel homeDetailsView = new HomeDetailsViewModel();
            homeDetailsView._Student = student;
            homeDetailsView._PageTitle = "学生详情";
            return View(homeDetailsView);  //默认查找同名视图
// HomeDetailsViewModel 
    public class HomeDetailsViewModel
    {
        public Student _Student { get; set; }
        public string _PageTitle { get; set; }
    }
~~~

~~~ html
@model ASPNETCore2Start.ViewModel.HomeDetailsViewModel; 
<body>
    <h3>@Model._PageTitle</h3>
    <div> 学号：@Model._Student._ID </div>
    <div> 姓名：@Model._Student._Name </div>
    <div> 年龄：@Model._Student._Age </div>
</body>
~~~



## 视图

更方便的模板化一部分 html中相同的部分

为什么要使用布局：

因为很多网页中都包含相同的组成部分，如果不弄这个，每个html文件都要去写这个，麻烦。

* Header
* Footer
* Menu
* View

### Razor布局

 **_Layout.cshtml**

在views文件夹下新建Shared文件夹，新建Razor布局。

![1605936751597](images/1605936751597.png)

~~~html
<!--> _Layout.cshtml <-->

<!DOCTYPE html>

<html>
<head>
    <meta name="viewport" content="width=device-width" />
    <title>@ViewBag.Title</title>
</head>
<body>
    <div>
        @RenderBody()
    </div>
</body>
</html>


~~~

**@RenderBody()** ：就表示在页面中的相应显示部分了。



**Details.cshtml**

然后在视图文件中修改相应代码

~~~html
@model TestAspDotNetEmpty.Model.Student
@{ 
    Layout = "/views/Shared/_Layout.cshtml";
    ViewBag.Title = "学生详情";
}

<div> @ViewBag.Title </div>
<div> 学号：@Model.m_nId </div>
<div> 姓名：@Model.m_strName </div>

~~~



### 节点Section

假设有一个自定义的JavaScripts文件，项目中只有部分视图会用到。那么就在这个视图中添加

比如**Details.cshtml**中

~~~html
@model TestAspDotNetEmpty.Model.Student
@{
    Layout = "/views/Shared/_Layout.cshtml";
    ViewBag.Title = "学生详情";
}

<div> @ViewBag.Title </div>
<div> 学号：@Model.m_nId </div>
<div> 姓名：@Model.m_strName </div>

@section Scripts {
    <script src="~/js/CustomScript.js"></script>
}
~~~

如果所有的都有这个脚本文件，那么则在  **_Layout.cshtml** 中添加

~~~html
<!DOCTYPE html>

<html>
<head>
    <meta name="viewport" content="width=device-width" />
    <title>@ViewBag.Title</title>
</head>
<body>
    <div>
        @RenderBody()
    </div>

    <!--
        是否必选,这个由显示的视图自己决定是否含有。
        比如details.cshtml中需要则可以在，details.html中添加

        @section Scripts {
            <script src="~/js/CustomScript.js"></script>
        }

        index.cshtml中不需要，则不添加上面的代码
    -->

    @RenderSection("Scripts", IsSectionDefined("Scripts"))

    <!--
        
    在所有视图文件中都需要，则可以在这里添加
        @section Scripts {
            <script src="~/js/CustomScript.js"></script>
        }
    -->
</body>
</html>

~~~



### _ViewStart.cshtml

在前面的Razor布局中，每一个.cshtml中都需要增加下列的路径（Layout = ""）,如果大量修改的话，则很麻烦，所以催生了这样一种方法，在 view开始前，调用不同的_layout

~~~html
@{
    Layout = "/views/Shared/_Layout.cshtml";
    ViewBag.Title = "学生详情";
}
~~~



**_ViewStart.cshtml**

**Views**文件夹中添加 Razor开始页面（**_ViewStart.cshtml**），并指定下列代码，用户的身份来指定输入那个视图。

~~~html
@{
    Layout = User.IsInRole("Guido") ? "_Admin" : "_Root";
}

~~~

![1605946987435](images/1605946987435.png)

**Shared**文件夹添加相应的 Layout视图（上图的:_Admin和__Root）

**Details.cshtml** 文件中，修改Layout属性

~~~html
@*原来*@
@{
    Layout = "/views/Shared/_Layout.cshtml";
    ViewBag.Title = "学生详情";
}
@*现在*@
@{
    ViewBag.Title = "学生详情";
}
~~~



### _ViewImports.cshtml

就是在加载视图之前，导入相应的包

比如：在Views文件夹下面添加

~~~html
@using TestAspDotNetEmpty.Model
~~~

![1605947811560](images/1605947811560.png)

那么视图中则从

![1605947881169](images/1605947881169.png)

修改为![1605947889391](images/1605947889391.png)

 同样，也可以在控制器文件夹下添加 _ViewImports.cshtml

![1605947946251](images/1605947946251.png)

### 总结：

​		**布局：**其实布局（_layout.cshtml）就相当于一个模板，然后自己建立那个（index.cshtml）就是相当于中间的一个部分。把他嵌套进去，一个套娃而已。

​		**节点：**就是一系列的功能接口脚本。

​		**视图开始：**就是加载视图开始的时候，首先的加载项，相当于首先定了布局。

​		**视图导入：**就是加载视图开始的时候，首先的加载项，相当于首先定了包。

​			加载顺序：首先 views文件夹下的 _ViewStart.cshtml或 _ViewImports.cshtml，然后控制器文件夹下的_ ViewStart.cshtml或_ViewImports.cshtml，如果有，就覆盖 Views文件夹下的。



## 路由

### 自定义路由

~~~C#
public void Configure(IApplicationBuilder app, IWebHostEnvironment env)
{
    app.UseStaticFiles();

    // 默认的路由 访问 Index()
    app.UseMvcWithDefaultRoute();

    // 自定义的路由 访问 Details()
    app.UseMvc(routes => routes.MapRoute("default", "{controller=Home}/{action=Details}/{id?}"));

}
~~~



 ![1605971735122](images/1605971735122.png)

![1605971805727](images/1605971805727.png)



### 属性路由

使用Route()属性定义路由，在Controller类或者Controller操作方法上应用Route()属性。

~~~c#
// StartUp中
public void Configure(IApplicationBuilder app, IWebHostEnvironment env)
{
    app.UseStaticFiles();

    app.UseMvc();
}

// HomeController
[Route("")]
[Route("Home")]
[Route("Home/Index")]
public IActionResult Index()
{
    return View(_studentRepository.GetStudents());
}

// 此种方式设置路径与控制器名称无关
[Route("Home/Details/{id?}")]
[Route("WC/Details/{id?}")]
public ViewResult Details(int? id)
{
    // C# 可空类型
	// ? : 单问号用于对 int,double,bool 等无法直接赋值为 null 的数据类型进行 null 的赋值，意思是这个数据类型是 Nullable 类型的。
	// int i; //默认值0
	// int? ii; //默认值null
	// ?? : 双问号 可用于判断一个变量在为 null 时返回一个指定的值。
    Student student = _studentRepository.GetStudent(id??0); 	// 为空时返回 0
    ViewData["PageTitle"] = "学生详情";
    return View(student);
}
~~~

<img src="images/1605973026306.png" alt="1605973026306" style="zoom:80%;" />

这种也可以访问，说明，控制器和路由没关系，只是为了效率，好开发，所以取相同名字。



在控制器上

~~~C#
[Route("Home")]
public class HomeController : Controller
{
    private readonly IStudentRepository _studentRepository;
    public HomeController(IStudentRepository student)
    {
        _studentRepository = student;
    }

    [Route("")]
    [Route("Index")]
    [Route("~/")]
    public IActionResult Index()
    {
        return View(_studentRepository.GetStudents());
    }

    [Route("Details/{id?}")]
    public ViewResult Details(int? id)
    {
        Student student = _studentRepository.GetStudent(id??0);
        ViewData["PageTitle"] = "学生详情";
        return View(student);
    }
}
~~~

**！！一般用路由模板就行了，在需要灵活的时候，就采用自定义路由。**



### UseEndpoints()

微软推荐使用这种

~~~c#
public void Configure(IApplicationBuilder app, IWebHostEnvironment env)
{
    app.UseStaticFiles();

    //app.UseMvcWithDefaultRoute();

    //app.UseMvc(routes => routes.MapRoute("default", "{controller=Home}/{action=Index}/{id?}"));

    app.UseRouting();

    app.UseEndpoints(endPoints => {
        endPoints.MapControllerRoute(
            name: "default",
            pattern: "{controller=Home}/{action=Index}/{id?}");
        });
}
~~~



## TagHelper

### 内置TagHelper

在_ViewImports.cshtml 中增加

~~~html
@addTagHelper *,Microsoft.AspNetCore.Mvc.TagHelpers
~~~

在代码中增加

![1606031896218](images/1606031896218.png)

好处：不是和模板拼接，在模板更改的情况下，同样可以访问到同样的地址。



### ImageHelper

![1606404156631](images/1606404156631.png)

给图片增加一个缓存，增加一个GUID，防止浏览器每次都访问服务器获取新图片，增加服务器的负载。

### EnvironmentTagHelper

比如要加载某个样式的时候，测试的时候可以不用，生产的时候采用，所以就可以用这个。

![1606404523997](images/1606404523997.png)



## 添加页面

![1606410132256](images/1606410132256.png)

使用表单创建

视图部分

~~~HTML
@* 
这里注意Student的构造函数，一定要有没有参数的，要不然，不能绑定模型 !!!!!!!!!!!!!!!!!! 
我TM在这里浪费了一晚上，卧槽，裂开了
*@
@model Student

    <form asp-controller="Student" asp-action="Create" method="post" class="mt-3">

        <div class="form-group row">
            <label asp-for="m_nId" class="col-sm-2 col-form-label"> 学号 </label>
            <div class="col-sm-5">
                <input asp-for="m_nId" type="text" class="form-control"  placeholder="请输入学号"/>
            </div>
            
        </div>

        <div class="form-group row">
            <label asp-for="m_nId" class="col-sm-2 col-form-label"> 姓名 </label>
            <div class="col-sm-5">
                <input asp-for="m_nId" type="text" class="form-control" placeholder="请输入姓名" />
            </div>
        </div>

        <div class="form-group row">
            <label asp-for="m_eClassName" class="col-sm-2 col-form-label"> 年级 </label>
            <div class="col-sm-5">
                <select asp-for="m_eClassName" asp-items="Html.GetEnumSelectList<EnumClassName>() " class="custom-select mr-sm-2" > </select>
            </div>         
        </div>

        <div class="form-group row">
            <div class="col-sm-10">
                <button type="submit" class="btn btn-primary" >
                    创建
                </button>
            </div>
        </div>
        

    </form>
~~~



### 添加提交按钮

~~~C#
[HttpGet]
public IActionResult Create()
{
   return View();
}

// 添加接口的属性 因为在页面点击添加按钮的时候，会有一个同名 Create Action，所以添加属性区分
// 这里注意Student的构造函数，一定要有没有参数的，要不然，不能绑定模型 !!!!!!!!!!!!!!!!!!
// 
[HttpPost]
public RedirectToActionResult Create(Student stu)
{
    Student newStu = _studentRepository.AddStudent(stu);
    return RedirectToAction("Details", new { id = newStu.Id });
}


~~~

