using System;
using System.Collections.Generic;

namespace ObserverPattern
{
    public class AbstractYaboFactory
    {
        public void Notify()
        {
            foreach (AbstractOldMan man in m_PersonList)
            {
                man.UpData();
            }
        }
        public void Dttach(AbstractOldMan man) { m_PersonList.Remove(man); }

        public void Attach(AbstractOldMan man) { m_PersonList.Add(man); }

        private List<AbstractOldMan> m_PersonList = new List<AbstractOldMan>();
    }

    public class AbstractOldMan
    {
        public virtual void UpData() { }
    }

    public class OldMan : AbstractOldMan
    {
        public OldMan(string strName) { m_strOldManName = strName; }

        override public void UpData()
        {
            Console.WriteLine("UpData  " + m_strOldManName);
        }

        private string m_strOldManName;
    }

    class Program
    {
        static void Main(string[] args)
        {
            OldMan oldMan_A = new OldMan("法外狂徒-张三");
            OldMan oldMan_B = new OldMan("章北海");
            OldMan oldMan_C = new OldMan("史强");
            OldMan oldMan_D = new OldMan("福贵");

            AbstractYaboFactory yaboFactory = new AbstractYaboFactory();
            yaboFactory.Attach(oldMan_A);
            yaboFactory.Attach(oldMan_B);
            yaboFactory.Attach(oldMan_C);
            yaboFactory.Attach(oldMan_D);

            yaboFactory.Notify();

            Console.ReadLine();
        }
    }
}
