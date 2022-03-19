#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QThread>
#include <QDebug>
#include "progressbarpage.h"
#include "progressbardialog.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::on_startDialogBtn_clicked()
{
    ProgressBarDialog * dialog = new ProgressBarDialog(this);

    QThread * thread = QThread::create([](){
       for( int i = 0; i < 100; ++i)
       {
           for( int j = 0; j < 50000000; ++j )
           {

           }

           qDebug() << "test：" << i;
       }
    });




    connect( thread, &QThread::finished, dialog, [&](){

        qDebug() << "dialog->close();";
        dialog->close();

    });
    connect( thread, &QThread::finished, thread, &QThread::deleteLater);
    connect( thread, &QThread::finished, dialog, &ProgressBarPage::deleteLater);


    thread->start();
    dialog->show();

    m_loop.exec();
    qDebug() << "test：" << "m_loop.exec();";

    // 这里不行，必须函数走完后才显示界面，如果增加在这里，进度条界面不会显示
    thread->quit();
    thread->wait();
    qDebug() << "test：" << "thread->wait();";
}

void MainWindow::on_starWidgetBtn_clicked()
{
    ProgressBarPage * page = new ProgressBarPage(this);

    QThread * thread = QThread::create([](){
       for( int i = 0; i < 100; ++i)
       {
           for( int j = 0; j < 50000000; ++j )
           {

           }

           qDebug() << "test：" << i;
       }
    });




    connect( thread, &QThread::finished, page, [&](){

        qDebug() << "page->close();";
        page->close();

    });

    connect( thread, &QThread::finished, thread, &QThread::deleteLater);
    connect( thread, &QThread::finished, page, &ProgressBarPage::deleteLater);


    thread->start();
    page->show();

    m_loop.exec();



    qDebug() << "test：" << "m_loop.exec();";

    // 这里不行，必须函数走完后才显示界面，如果增加在这里，进度条界面不会显示
    thread->quit();
    thread->wait();

    qDebug() << "test：" << "thread->wait();";
}
