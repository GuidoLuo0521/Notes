using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

/// <summary>
/// 以生产鸭脖为例子
/// 每个鸭脖的组成过程都是一致的，但是使用同样的构建过程可以创建不同的表示(即可以组装成不一样味道的鸭脖)
/// 生产鸭脖的这个场景就可以应用建造者模式来设计
/// </summary>
namespace BuilderPatternClass
{
    /// <summary>
    /// 客户类
    /// </summary>
    class OldMan
    {
        static void Main(string[] args)
        {
            // 老头找老板说要买鸭脖，
            // 创建老板和工人
            Boss boss = new Boss();
            Worker zhangsan = new WorkerZhangSan();
            Worker lisi = new WorkerLiSi();

            // 老板叫张三去生产鸭脖，这里老板控制总流程
            // 所以，这里老板也可以抽象，每个老板生产不同的东西，或者流程不一样，
            // 比如老板 B 先加辣椒再加盐巴
            boss.ToProductYaBo(zhangsan);

            // 获取鸭脖
            YaBo yabo = zhangsan.GetYaBo();
            yabo.Show();

            // 获取鸭脖
            boss.ToProductYaBo(lisi);
            YaBo yabo2 = lisi.GetYaBo();
            yabo2.Show();

            Console.Read();
        }
    }

    /// <summary>
    /// 张三和李四，老板没给工资是不会去的，所以，必须老板叫他们他们才去，这时候就要老板叫某人了，去做什么做什么
    /// 老板也就是建造者模式中的指挥者，张三李四就是工人，就像个机器人
    /// 指挥创建过程类
    /// </summary>
    public class Boss
    {
        // 组装鸭脖
        public void ToProductYaBo(Worker builder)
        {
            builder.BuildPartSalt();
            builder.BuildPartLaJiao();
        }
    }

    /// <summary>
    /// 鸭脖
    /// </summary>
    public class YaBo
    {
        // 鸭脖调料集合
        private IList<string> parts = new List<string>();

        // 把调料添加到鸭脖里面
        public void Add(string part)
        {
            parts.Add(part);
        }

        public void Show()
        {
            Console.WriteLine("开始生产鸭脖.......");
            foreach (string part in parts)
            {
                Console.WriteLine(part + "已加入");
            }

            Console.WriteLine("鸭脖已经生产好了");
        }
    }

    /// <summary>
    /// 抽象建造者，这个场景下为 "工人" ，这里也可以定义为接口
    /// </summary>
    public abstract class Worker
    {
        // 放盐
        public abstract void BuildPartSalt();
        // 放辣椒
        public abstract void BuildPartLaJiao();

        // 其他香料。。。这里省略

        // 返回鸭脖
        public abstract YaBo GetYaBo();
    }

    /// <summary>
    /// 具体创建者，具体的某个人为具体创建者，例如：装机小王啊
    /// </summary>
    public class WorkerZhangSan : Worker
    {
        YaBo yabo = new YaBo();

        public override void BuildPartSalt()
        {
            yabo.Add("盐巴");
        }

        public override void BuildPartLaJiao()
        {
            yabo.Add("魔鬼椒");
        }

        public override YaBo GetYaBo()
        {
            return yabo;
        }
    }

    /// <summary>
    /// 具体创建者，具体的某个人为具体创建者，例如：装机张三啊，可能他放的盐巴多一点或者辣椒不一样
    /// </summary>
    public class WorkerLiSi : Worker
    {
        YaBo yabo = new YaBo();
        public override void BuildPartSalt()
        {
            yabo.Add("盐巴巴巴");
        }

        public override void BuildPartLaJiao()
        {
            yabo.Add("朝天椒");
        }

        public override YaBo GetYaBo()
        {
            return yabo;
        }
    }
}