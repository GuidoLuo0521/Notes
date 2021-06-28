using System;
using System.Collections.Generic;

namespace BridgePattern
{
    class Program
    {
        // 客户端调用
        // 类似Web应用程序
        class Client
        {
            static void Main(string[] args)
            {
                BusinessObject customers = new CustomersBusinessObject("ShangHai");
                customers.Dataacces = new CustomersDataAccess();

                customers.Add("小六");
                Console.WriteLine("增加了一位成员的结果：");
                customers.ShowAll();
                customers.Delete("王五");
                Console.WriteLine("删除了一位成员的结果：");
                customers.ShowAll();
                Console.WriteLine("更新了一位成员的结果：");
                customers.Update("Learning_Hard");
                customers.ShowAll();

                Console.Read();
            }
        }

        // BLL 层  业务逻辑层
        public class BusinessObject
        {
            // 字段
            private DataAccess dataacess;
            private string city;

            public BusinessObject(string city)
            {
                this.city = city;
            }

            // 属性
            public DataAccess Dataacces
            {
                get { return dataacess; }
                set { dataacess = value; }
            }

            // 方法
            public virtual void Add(string name)
            {
                Dataacces.AddRecord(name);
            }

            public virtual void Delete(string name)
            {
                Dataacces.DeleteRecord(name);
            }

            public virtual void Update(string name)
            {
                Dataacces.UpdateRecord(name);
            }

            public virtual string Get(int index)
            {
                return Dataacces.GetRecord(index);
            }
            public virtual void ShowAll()
            {
                Console.WriteLine();
                Console.WriteLine("{0}的顾客有：", city);
                Dataacces.ShowAllRecords();
            }
        }

        public class CustomersBusinessObject : BusinessObject
        {
            public CustomersBusinessObject(string city)
                : base(city) { }

            // 重写方法
            public override void ShowAll()
            {
                Console.WriteLine("------------------------");
                base.ShowAll();
                Console.WriteLine("------------------------");
            }
        }

        /// <summary>
        /// 相当于三层架构中数据访问层（DAL）
        /// </summary>
        public abstract class DataAccess
        {
            // 对记录的增删改查操作
            public abstract void AddRecord(string name);
            public abstract void DeleteRecord(string name);
            public abstract void UpdateRecord(string name);
            public abstract string GetRecord(int index);
            public abstract void ShowAllRecords();
        }

        public class CustomersDataAccess : DataAccess
        {
            // 字段
            private List<string> customers = new List<string>();

            public CustomersDataAccess()
            {
                // 实际业务中从数据库中读取数据再填充列表
                customers.Add("Learning Hard");
                customers.Add("张三");
                customers.Add("李四");
                customers.Add("王五");
            }
            // 重写方法
            public override void AddRecord(string name)
            {
                customers.Add(name);
            }

            public override void DeleteRecord(string name)
            {
                customers.Remove(name);
            }

            public override void UpdateRecord(string updatename)
            {
                customers[0] = updatename;
            }

            public override string GetRecord(int index)
            {
                return customers[index];
            }

            public override void ShowAllRecords()
            {
                foreach (string name in customers)
                {
                    Console.WriteLine(" " + name);
                }
            }

        }
    }
}
