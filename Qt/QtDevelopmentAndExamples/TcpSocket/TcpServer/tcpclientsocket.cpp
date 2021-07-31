#include "tcpclientsocket.h"

TcpClientSocket::TcpClientSocket(QObject *parent)
{

    // 继承自 QIODevice，QIODevice是所有输入输出设备的抽象类
    // QAbstractSocket : public QIODevice     QIODevice::readyRead();
    // QTcpSocket : public QAbstractSocket      QAbstractSocket::disconnected();

    // readyRead 信号在有数据来的时候发出
    connect( this, SIGNAL(readyRead()), this, SLOT(OnDateRecevied()));

    // 断开连接
    connect( this, SIGNAL(disconnected()), this, SLOT(OnDisConnected()));
}

void TcpClientSocket::OnDateRecevied()
{
    while (bytesAvailable() > 0)
    {
        int nLen = bytesAvailable();
        char buffer[nLen] ;
        read(buffer, nLen);

        QString str = QString::fromUtf8(buffer);
        emit ClientSentMessageSignal( str);
    }
}

void TcpClientSocket::OnDisConnected()
{
    emit DisConnectedSignal(this->socketDescriptor());
}
