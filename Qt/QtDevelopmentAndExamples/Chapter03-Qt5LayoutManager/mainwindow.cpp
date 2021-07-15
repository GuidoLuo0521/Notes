#include "mainwindow.h"
#include "ui_mainwindow.h"


#include <QDockWidget>
#include <QFile>
#include <QIODevice>
#include <QLabel>
#include <QListWidget>
#include <QSplitter>
#include <QStackedWidget>
#include <QTextEdit>
#include <QTextStream>

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


void MainWindow::on_btnSplitter_clicked()
{
    QSplitter * pSplitterMain = new QSplitter(Qt::Horizontal, 0);
    pSplitterMain->setAttribute(Qt::WA_DeleteOnClose);

    QTextEdit * pTextEditLeft = new QTextEdit("Left", pSplitterMain);

    QSplitter * pSplitterRight = new QSplitter(Qt::Vertical, pSplitterMain);
    QTextEdit * pTextEditRightTop = new QTextEdit("Right Top", pSplitterRight);
    QTextEdit * pTextEditRightBottom = new QTextEdit("Right Bottom", pSplitterRight);

    pSplitterMain->show();
}

void MainWindow::on_btnDock_clicked()
{
    QMainWindow * pMainWindow = new QMainWindow;
    pMainWindow->setAttribute(Qt::WA_DeleteOnClose);

    // 设定主窗口
    QTextEdit * pTextEdit = new QTextEdit("Main Window", pMainWindow);
    pMainWindow->setCentralWidget(pTextEdit);

    // 设定第一个浮动窗口
    QDockWidget * pDockWidget = new QDockWidget("DockWidget1", pMainWindow);

    // 可移动
    pDockWidget->setFeatures(QDockWidget::DockWidgetMovable);
    pDockWidget->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);

    // 这里因为，DockWidget 只是一个容器，所以需要自己创建一个 Widget 来防止 btn和Text
    QWidget * pWidget = new QWidget();
    QTextEdit * pTextEdit1 = new QTextEdit("Text1");
    QPushButton * pBtn1 = new QPushButton("Btn");

    QHBoxLayout * pLayout = new QHBoxLayout(pDockWidget);
    pLayout->addWidget(pTextEdit1);
    pLayout->addWidget(pBtn1);

    pWidget->setLayout(pLayout);
    pDockWidget->setWidget(pWidget);
    pMainWindow->addDockWidget(Qt::RightDockWidgetArea, pDockWidget);

    // 第二个浮动窗口
    QDockWidget * pDockWidget2 = new QDockWidget("DockWidget2", pMainWindow);
    pDockWidget2->setFeatures(QDockWidget::DockWidgetMovable | QDockWidget::DockWidgetClosable);
    pDockWidget2->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);

    QTextEdit * pTextEdit2 = new QTextEdit("Text2", pMainWindow);
    pDockWidget2->setWidget(pTextEdit2);
    pMainWindow->addDockWidget(Qt::RightDockWidgetArea, pDockWidget2);

    // 第三个浮动窗口
    QDockWidget * pDockWidget3 = new QDockWidget("DockWidget3", pMainWindow);
    pDockWidget3->setFeatures(QDockWidget::DockWidgetMovable |
                              QDockWidget::DockWidgetClosable |
                              QDockWidget::DockWidgetFloatable);
    pDockWidget3->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);

    QTextEdit * pTextEdit3 = new QTextEdit("Text3", pMainWindow);
    pDockWidget3->setWidget(pTextEdit3);
    pMainWindow->addDockWidget(Qt::RightDockWidgetArea, pDockWidget3);

    pMainWindow->show();

}

void MainWindow::on_btnStacked_clicked()
{
    //QWidget * pMainWindow = new QWidget;
    QMainWindow * pMainWindow = new QMainWindow;
    //pMainWindow->setCentralWidget();

    pMainWindow->setAttribute(Qt::WA_DeleteOnClose);

    QListWidget * pList = new QListWidget(pMainWindow);  //新建一个QListWidget对象
    pList->insertItem(0, ("window0"));  //插入三个条目
    pList->insertItem(1, ("window1"));
    pList->insertItem(2, ("window2"));

    QLabel * label0 = new QLabel(("windowTest0"));  //新建三个标签对象，作为堆栈窗口需要显示的三层窗体
    QLabel * label1 = new QLabel(("windowTest1"));
    QLabel * label2 = new QLabel(("windowTest2"));

    QStackedWidget* pStack = new QStackedWidget(pMainWindow);  //新建一个堆栈窗体对象
    pStack->addWidget(label0);       //将新建的三个QLabel标签控件依次插入堆栈窗体中
    pStack->addWidget(label1);
    pStack->addWidget(label2);

    QHBoxLayout *pMainLayout = new QHBoxLayout(); //对整个对话框进行布局
    pMainLayout->setMargin(5); //设置对话框的边距为5
    pMainLayout->setSpacing(5); //设置各个控件之间的间距为5
    pMainLayout->addWidget(pList);
    pMainLayout->addWidget(pStack, 0, Qt::AlignHCenter);
    pMainLayout->setStretchFactor(pList, 1);  //设置list为可伸缩控件
    pMainLayout->setStretchFactor(pStack,3);

    pMainWindow->setLayout(pMainLayout);

    //将 QListWidget的currentRowChanged信号和堆栈窗体的setCurrentIndex槽函数连接起来，实现按选择显示窗体。
    connect(pList, SIGNAL(currentRowChanged(int)), pStack, SLOT(setCurrentIndex(int)));

    pMainWindow->show();
}

void MainWindow::on_btnRead_clicked()
{
    QFile file("f:\\tst230.bin");
    if( file.open( QIODevice::ReadOnly) )
    {
        ui->textEdit->clear();
        QTextStream stream(&file);
        QString str = stream.readAll();
        QByteArray str2 = str.toUtf8();
        ui->textEdit->append(str2.toHex().toUpper());
    }
}
