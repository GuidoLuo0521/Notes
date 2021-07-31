#ifndef TCPSERVER_H
#define TCPSERVER_H

#include <QTcpServer>
#include <tcpclientsocket.h>

class TcpServer : public QTcpServer
{
    Q_OBJECT
public:
    TcpServer(QObject * parent = 0, int nPort = 0);

signals:
    void UpdateServerUi(QString msg);

public slots:
    // 处理客户端已发送消息的信号
    void OnClientSentMessage(QString msg);

    // 断开链接 通过 socked 描述符 删除
    void OnDisConnected(int nDesc);

    // 对发送来的客户端信息进行广播
    void NotifyAllClients(QString msg);

protected:
    // 当有一个新连接的时候，触发这个函数 增加 客户端
    void incomingConnection(qintptr handle) override;

private:
    // 保存每一个客户端 socket
    QList<TcpClientSocket *> m_listTcpClientSocket;
};

#endif // TCPSERVER_H
