#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QHostAddress>
#include <QMainWindow>
#include <QTcpSocket>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_btnSend_clicked();
    void on_btnJoinChatRoom_clicked();

    void OnConnected();
    void OnDisConnected();
    void OnDataRecived();

    void on_leUserName_textChanged(const QString &arg1);

    void OnSendMsgToServer(const QString arg1);
private:
    Ui::MainWindow *ui;

    bool m_bStaus;
    int m_nPort;
    QString m_strUserName;
    QHostAddress * m_pServerIP;
    QTcpSocket * m_pTcpSocket;
};
#endif // MAINWINDOW_H
