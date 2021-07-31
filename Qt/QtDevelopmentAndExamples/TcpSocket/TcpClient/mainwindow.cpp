#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDateTime>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , m_bStaus(false)
    , m_nPort(8888)
    , m_pServerIP(nullptr)
    , m_pTcpSocket(nullptr)
{
    ui->setupUi(this);
    ui->leUserName->setText("李云龙");
    ui->lePort->setText(QString("%1").arg(m_nPort));
    ui->leServerAddress->setText(QString("127.0.0.1"));
    ui->btnSend->setEnabled(m_bStaus);

    ui->btnSend->setShortcut(Qt::Key_Enter);
    ui->btnSend->setShortcut(Qt::Key_Return);

    this->setWindowTitle("客户端 用户：李云龙");

    m_pServerIP = new QHostAddress(QString("127.0.0.1"));
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_btnSend_clicked()
{
    QString str = ui->lineEdit->text();
    if( str != "" )
    {
        QString msg = QString("%1:%2").arg(m_strUserName).arg(str);
        OnSendMsgToServer(msg);

        ui->lineEdit->clear();
    }
}

void MainWindow::on_btnJoinChatRoom_clicked()
{
    if( m_bStaus == false )
    {
        QString str = ui->leServerAddress->text();
        if( m_pServerIP->setAddress(str) == false )
        {
            QMessageBox::critical(this, "错误", QString("服务器地址错误:%1").arg(str));
            return;
        }

        str = ui->leUserName->text();
        if( str == "" )
        {
            QMessageBox::critical(this, "错误", "用户名不能为空");
            return;
        }
        m_strUserName = str;

        m_pTcpSocket = new QTcpSocket(this);
        connect( m_pTcpSocket, &QTcpSocket::connected, this, &MainWindow::OnConnected);
        connect( m_pTcpSocket, &QTcpSocket::disconnected, this, &MainWindow::OnDisConnected);
        connect( m_pTcpSocket, &QTcpSocket::readyRead, this, &MainWindow::OnDataRecived);

        m_pTcpSocket->connectToHost(*m_pServerIP, m_nPort);
        QAbstractSocket::SocketState state = m_pTcpSocket->state()  ;
        if( state != QAbstractSocket::ConnectingState)
        {
            QMessageBox::critical(this, "错误", QString("聊天室未开放。").arg(str));
            return;
        }

        QString msg = QString("%1，进入聊天室").arg(m_strUserName);
        OnSendMsgToServer(msg);
    }
    else
    {
        QString msg = QString("%1，离开聊天室").arg(m_strUserName);
        OnSendMsgToServer(msg);
        m_pTcpSocket->disconnectFromHost();
    }
}

void MainWindow::OnConnected()
{
    m_bStaus = true;
    ui->btnSend->setEnabled(m_bStaus);
    ui->btnJoinChatRoom->setText("离开聊天室");
}

void MainWindow::OnDisConnected()
{
    m_bStaus = false;
    ui->btnSend->setEnabled(m_bStaus);
    ui->btnJoinChatRoom->setText("进入聊天室");
}

void MainWindow::OnDataRecived()
{
    while (m_pTcpSocket->bytesAvailable() > 0)
    {
        //int nLen = m_pTcpSocket->bytesAvailable();
        //char buffer[nLen];
        //m_pTcpSocket->read(buffer, nLen);
        //QString str = QString::fromUtf8(buffer);
        //str.append("\0");

        QByteArray datagram;
        datagram.resize(m_pTcpSocket->bytesAvailable());
        m_pTcpSocket->read(datagram.data(), datagram.size());

        QString str(datagram);
        ui->textEdit->append(str);
    }
}

void MainWindow::on_leUserName_textChanged(const QString &arg1)
{
    this->setWindowTitle("客户端 用户：" + arg1);
    m_strUserName = arg1;
}

void MainWindow::OnSendMsgToServer(const QString msg)
{
    QString strTime = QDateTime::currentDateTime().toString("hh:mm:ss ");
    strTime += msg;
    QByteArray datastream = strTime.toUtf8().data();
    datastream += '\0';
    if(m_pTcpSocket->write(datastream, datastream.size()) != datastream.size() )
        return;
}
