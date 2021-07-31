#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <tcpserver.h>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

signals:
    void UpdateServerUi(QString msg);

public slots:
    void OnCreateServer();
    void OnCloseServer();
    void OnUpdateServerUi(QString msg);

private slots:
    void on_btnCreateChatRoom_clicked();

private:
    bool m_bChatRoonRunning;
    int m_nPort ;
    TcpServer * m_pTcpServer;
};
#endif // MAINWINDOW_H
