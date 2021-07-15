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

    // �趨������
    QTextEdit * pTextEdit = new QTextEdit("Main Window", pMainWindow);
    pMainWindow->setCentralWidget(pTextEdit);

    // �趨��һ����������
    QDockWidget * pDockWidget = new QDockWidget("DockWidget1", pMainWindow);

    // ���ƶ�
    pDockWidget->setFeatures(QDockWidget::DockWidgetMovable);
    pDockWidget->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);

    // ������Ϊ��DockWidget ֻ��һ��������������Ҫ�Լ�����һ�� Widget ����ֹ btn��Text
    QWidget * pWidget = new QWidget();
    QTextEdit * pTextEdit1 = new QTextEdit("Text1");
    QPushButton * pBtn1 = new QPushButton("Btn");

    QHBoxLayout * pLayout = new QHBoxLayout(pDockWidget);
    pLayout->addWidget(pTextEdit1);
    pLayout->addWidget(pBtn1);

    pWidget->setLayout(pLayout);
    pDockWidget->setWidget(pWidget);
    pMainWindow->addDockWidget(Qt::RightDockWidgetArea, pDockWidget);

    // �ڶ�����������
    QDockWidget * pDockWidget2 = new QDockWidget("DockWidget2", pMainWindow);
    pDockWidget2->setFeatures(QDockWidget::DockWidgetMovable | QDockWidget::DockWidgetClosable);
    pDockWidget2->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);

    QTextEdit * pTextEdit2 = new QTextEdit("Text2", pMainWindow);
    pDockWidget2->setWidget(pTextEdit2);
    pMainWindow->addDockWidget(Qt::RightDockWidgetArea, pDockWidget2);

    // ��������������
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

    QListWidget * pList = new QListWidget(pMainWindow);  //�½�һ��QListWidget����
    pList->insertItem(0, ("window0"));  //����������Ŀ
    pList->insertItem(1, ("window1"));
    pList->insertItem(2, ("window2"));

    QLabel * label0 = new QLabel(("windowTest0"));  //�½�������ǩ������Ϊ��ջ������Ҫ��ʾ�����㴰��
    QLabel * label1 = new QLabel(("windowTest1"));
    QLabel * label2 = new QLabel(("windowTest2"));

    QStackedWidget* pStack = new QStackedWidget(pMainWindow);  //�½�һ����ջ�������
    pStack->addWidget(label0);       //���½�������QLabel��ǩ�ؼ����β����ջ������
    pStack->addWidget(label1);
    pStack->addWidget(label2);

    QHBoxLayout *pMainLayout = new QHBoxLayout(); //�������Ի�����в���
    pMainLayout->setMargin(5); //���öԻ���ı߾�Ϊ5
    pMainLayout->setSpacing(5); //���ø����ؼ�֮��ļ��Ϊ5
    pMainLayout->addWidget(pList);
    pMainLayout->addWidget(pStack, 0, Qt::AlignHCenter);
    pMainLayout->setStretchFactor(pList, 1);  //����listΪ�������ؼ�
    pMainLayout->setStretchFactor(pStack,3);

    pMainWindow->setLayout(pMainLayout);

    //�� QListWidget��currentRowChanged�źźͶ�ջ�����setCurrentIndex�ۺ�������������ʵ�ְ�ѡ����ʾ���塣
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
