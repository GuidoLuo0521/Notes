#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QUdpSocket>

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
    void on_btnClose_clicked();

    void OnReceived();

private:
    Ui::MainWindow *ui;

    QUdpSocket * m_pUdpSocket;
    int m_nPort = 5555;
};
#endif // MAINWINDOW_H
