#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QPainter>
#include <QTime>
#include <QHBoxLayout>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->setMouseTracking(true);
    this->centralWidget()->setMouseTracking(true);

    m_pCrntMousePos = new QLabel("当前鼠标位置：（0，0）");
    ui->statusbar->addPermanentWidget(m_pCrntMousePos);// 永久信息显示，永久信息在状态栏最右侧

    m_pLeftMousePos = new QLabel("上次左键按下位置：（0，0）");
    ui->statusbar->addPermanentWidget(m_pLeftMousePos);

    m_pRightMousePos = new QLabel("上次右键按下位置：（0，0）");
    ui->statusbar->addPermanentWidget(m_pRightMousePos);

    // 显示一会儿，自动消失
    ui->statusbar->showMessage(QDateTime::currentDateTime().toString("hh:mm:ss"), 10 *1000);

    m_Pixmap.load(":/icons/icons/pic.png");


    m_pLeftLable = new QLabel();
    m_pCenterLable = new QLabel();
    m_pRightLable = new QLabel();

    m_LeftPixmap.load(":/icons/icons/butterfly.png");
    m_CenterPixmap.load(":/icons/icons/butterfly.png");
    m_RightPixmap.load(":/icons/icons/butterfly.png");


    m_pLeftLable->setPixmap(m_LeftPixmap);
    m_pCenterLable->setPixmap(m_CenterPixmap);
    m_pRightLable->setPixmap(m_RightPixmap);

    m_pLeftLable->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    m_pCenterLable->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    m_pRightLable->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);


    m_pLeftLable->installEventFilter(this);
    m_pCenterLable->installEventFilter(this);
    m_pRightLable->installEventFilter(this);


    QHBoxLayout * pMainLayout = new QHBoxLayout();
    pMainLayout->addWidget(m_pLeftLable);
    pMainLayout->addWidget(m_pCenterLable);
    pMainLayout->addWidget(m_pRightLable);
    this->centralWidget()->setLayout(pMainLayout);
}

MainWindow::~MainWindow()
{
    delete ui;
}

bool MainWindow::eventFilter(QObject * watched, QEvent * event)
{
    if(watched == m_pLeftLable)
    {
        if(event->type() == QEvent::MouseButtonPress)
        {
            m_LeftPixmap.scaled(m_LeftPixmap.width() * 1.5, m_LeftPixmap.height() * 1.5);
            m_pLeftLable->setPixmap(m_LeftPixmap);
            m_pLeftLable->update();

            return true;
        }
    }

    if(watched == m_pRightLable)
    {
        if(event->type() == QEvent::KeyPress)
        {
            m_RightPixmap.scaled(m_RightPixmap.width() * 0.8, m_RightPixmap.height() * 0.8);
            m_pRightLable->setPixmap(m_RightPixmap);
            m_pRightLable->update();

            return true;
        }
    }

    // 返回给上层的事件过滤器
    return QWidget::eventFilter(watched, event);
}

void MainWindow::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.drawPixmap(m_PixmapX, m_PixmapY, m_Pixmap.width(), m_Pixmap.height(), m_Pixmap);
}

void MainWindow::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::MouseButton::LeftButton)
        m_pLeftMousePos->setText(QString("上次左键按下位置：（%1，%2）").arg(event->x()).arg(event->y()));
    if(event->button() == Qt::MouseButton::RightButton)
        m_pRightMousePos->setText(QString("上次右键按下位置：（%1，%2）").arg(event->x()).arg(event->y()));



    ui->statusbar->update();
}

void MainWindow::mouseMoveEvent(QMouseEvent *event)
{
    m_pCrntMousePos->setText(QString("当前鼠标位置：（%1，%2）").arg(event->x()).arg(event->y()));
    ui->statusbar->update();
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    if( event->key() == Qt::Key_Left )  m_PixmapX -= 1;
    if( event->key() == Qt::Key_Right ) m_PixmapX += 1;
    if( event->key() == Qt::Key_Up )    m_PixmapY -= 1;
    if( event->key() == Qt::Key_Down )  m_PixmapY += 1;

    update();
}

void MainWindow::keyReleaseEvent(QKeyEvent *event)
{
    if( event->key() == Qt::Key_Space )  {m_PixmapX = 0; m_PixmapY = 0;}

    update();
}

