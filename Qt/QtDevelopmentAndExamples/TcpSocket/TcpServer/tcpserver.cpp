#include "tcpserver.h"


TcpServer::TcpServer(QObject *parent, int nPort)
{
    // 在指定的端口，对任意地址进行监听 （0,0,0,0）
    listen(QHostAddress::Any, nPort);
}

void TcpServer::OnClientSentMessage(QString msg)
{
    emit UpdateServerUi(msg);

    NotifyAllClients(msg);
}

void TcpServer::OnDisConnected(int nDesc)
{
    for( int i = 0; i < m_listTcpClientSocket.count(); ++i )
    {
        if( nDesc == m_listTcpClientSocket[i]->socketDescriptor() )
        {
            m_listTcpClientSocket.removeAt(i);
            break;
        }
    }
}

void TcpServer::NotifyAllClients(QString msg)
{
    for( int i = 0; i < m_listTcpClientSocket.count(); ++i )
    {
        QTcpSocket * p = m_listTcpClientSocket.at(i);

        QByteArray datastream = msg.toUtf8().data();
        if(p->write(datastream, datastream.size()) != datastream.size() )
            continue;
    }
}

void TcpServer::incomingConnection(qintptr handle)
{
    TcpClientSocket * p = new TcpClientSocket(this);

    connect( p, SIGNAL(ClientSentMessageSignal(QString)), this, SLOT(OnClientSentMessage(QString)));
    connect( p, SIGNAL(DisConnectedSignal(int)), this, SLOT(OnDisConnected( int)));

    p->setSocketDescriptor(handle);
    m_listTcpClientSocket.append(p);
}
