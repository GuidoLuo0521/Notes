#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , m_bChatRoonRunning(false)
    , m_nPort(8888)
    , m_pTcpServer(nullptr)
{
    ui->setupUi(this);

    this->setWindowTitle("服务端");
    ui->lePort->setText(QString("%1").arg(m_nPort));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::OnCreateServer()
{
    if(m_pTcpServer == nullptr && m_bChatRoonRunning == false)
    {
        m_pTcpServer = new TcpServer(this, m_nPort);
        connect( m_pTcpServer, SIGNAL(UpdateServerUi(QString)), this, SLOT(OnUpdateServerUi(QString)) );

        ui->btnCreateChatRoom->setText("关闭聊天室");
        m_bChatRoonRunning = true;

        QString msg = "等待朋友加入...";
        OnUpdateServerUi( msg);
    }
}

void MainWindow::OnCloseServer()
{
    m_pTcpServer->OnClientSentMessage( "服务器：老子不干了~~ 再见~~");

    if( m_pTcpServer != nullptr && m_bChatRoonRunning == true)
    {
        delete m_pTcpServer;
        m_pTcpServer = nullptr;

        ui->btnCreateChatRoom->setText("开启聊天室");
        m_bChatRoonRunning = false;
    }
}

void MainWindow::OnUpdateServerUi(QString msg)
{
    ui->textEdit->append(msg);
}

void MainWindow::on_btnCreateChatRoom_clicked()
{
    m_bChatRoonRunning ? OnCloseServer() : OnCreateServer();
}
