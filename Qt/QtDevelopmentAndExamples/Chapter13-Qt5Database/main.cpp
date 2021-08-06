#include "mainwindow.h"

#include <QApplication>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QDebug>
#include <QSqlError>

#include <QSqlTableModel>
#include <QTableView>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //MainWindow w;
    //w.show();

    {
        //添加数据库驱动
        QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
        //设置数据库名称
        db.setDatabaseName(":memory:");
        //打开数据库
        if(!db.open())
        {
            return false;
        }

        //以下执行相关sql语句
        QSqlQuery query;

        //新建student表，id设置为主键，还有一个name项
        query.exec("create table student(id int primary key,name varchar)");

        //向表中插入3条记录
        query.exec("insert into student values(1,'xiaogang')");
        query.exec("insert into student values(2,'xiaoming')");
        query.exec("insert into student values(3,'xiaohong')");

        //查找表中id >=2 的记录的id项和name项的值
        query.exec("select id,name from student where id >= 2");

        //query.next()指向查找到的第一条记录，然后每次后移一条记录
        while(query.next())
        {
            //query.value(0)是id的值，将其转换为int型
            int value0 = query.value(0).toInt();
            QString value1 = query.value(1).toString();
            //输出两个值
            qDebug() << value0 << value1 ;
        }

        db.close();

    }

#if 0
    QSqlDatabase::removeDatabase(":memory:");
#else
    QString name;
    {
        name = QSqlDatabase::database().connectionName();
    }//超出作用域，隐含对象QSqlDatabase::database()被删除。
    QSqlDatabase::removeDatabase(name);
#endif


    QSqlDatabase staticecgdb = QSqlDatabase::addDatabase("QMYSQL", "MySQL_alan");
    staticecgdb.setHostName("localhost");
    staticecgdb.setPort(3306);
    staticecgdb.setDatabaseName("alan");
    staticecgdb.setUserName("root");
    staticecgdb.setPassword("");

    if(staticecgdb.open())
    {
        QSqlTableModel *model = new QSqlTableModel( nullptr, staticecgdb);
        model->setTable("userinfo");
        model->setEditStrategy(QSqlTableModel::OnManualSubmit);

        if(model->select())
        {
            model->setHeaderData(0, Qt::Horizontal, "id");
            model->setHeaderData(1, Qt::Horizontal, "username");
            model->setHeaderData(1, Qt::Horizontal, "password");

            QTableView *view = new QTableView;
            view->setModel(model);
            view->show();
        }
    }

    return a.exec();
}
