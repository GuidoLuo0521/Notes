#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->setWindowTitle("UDP Client");

    m_pUdpSocket = new QUdpSocket(this);
    connect(m_pUdpSocket, &QUdpSocket::readyRead, this, &MainWindow::OnReceived);

    bool bResult = m_pUdpSocket->bind(m_nPort);
    if( bResult == false )
    {
        QMessageBox::warning(this, "警告", "端口绑定失败~");
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_btnClose_clicked()
{
    this->close();
}

void MainWindow::OnReceived()
{
    ui->textEdit->clear();

    while (m_pUdpSocket->hasPendingDatagrams())
    {
        QByteArray datagram;
        datagram.resize(m_pUdpSocket->pendingDatagramSize());
        m_pUdpSocket->readDatagram(datagram.data(), datagram.size());

        QString str = datagram.data();
        ui->textEdit->append(str.toLocal8Bit().data());
    }
}
