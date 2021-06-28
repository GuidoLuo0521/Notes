using System;
using System.Collections.Generic;
using System.Text;

namespace SingletonPattern
{
    // 缺点：多线程不好使用

    class SignalThreadSingleton
    {
        // 定义一个静态变量来保存类的实例
        private static SignalThreadSingleton uniqueInstance;

        // 定义私有构造函数，使外界不能创建该类实例
        private SignalThreadSingleton()
        {
        }

        /// <summary>
        /// 定义公有方法提供一个全局访问点,同时你也可以定义公有属性来提供全局访问点
        /// </summary>
        /// <returns></returns>
        public static SignalThreadSingleton GetInstance()
        {
            // 如果类的实例不存在则创建，否则直接返回
            if (uniqueInstance == null)
            {
                uniqueInstance = new SignalThreadSingleton();
            }
            return uniqueInstance;
        }
    }
}
