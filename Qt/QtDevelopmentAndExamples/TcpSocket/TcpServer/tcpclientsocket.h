#ifndef TCPCLIENTSOCKET_H
#define TCPCLIENTSOCKET_H

#include <QTcpSocket>


class TcpClientSocket : public QTcpSocket
{
    Q_OBJECT

public:
    TcpClientSocket(QObject * parent = 0);

signals:
    void ClientSentMessageSignal(QString);
    void DisConnectedSignal(int);

protected slots:
    void OnDateRecevied();
    void OnDisConnected();

protected:

};

#endif // TCPCLIENTSOCKET_H
