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
        m_pUdpSocket->writeDatagram(
            str.toUtf8(),
            str.count(),
            QHostAddress::Broadcast, m_nPort);
    }
}

void MainWindow::on_textEdit_textChanged()
{
    on_btnSendPause_clicked();
}
