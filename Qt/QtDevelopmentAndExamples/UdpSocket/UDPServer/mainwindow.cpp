#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->setWindowTitle("UDP Server");

    m_pUdpSocket = new QUdpSocket(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_btnSendPause_clicked()
{
    QString str = ui->textEdit->toPlainText();
    if( str != "")
    {
        QByteArray datagram = str.toUtf8().data();

        bool bRet = m_pUdpSocket->writeDatagram(
            datagram,
            datagram.size(),
            QHostAddress::Broadcast, m_nPort) == datagram.size();
        if(bRet)
            qDebug() << "发送成功" ;

    }
}

void MainWindow::on_textEdit_textChanged()
{
    on_btnSendPause_clicked();
}
