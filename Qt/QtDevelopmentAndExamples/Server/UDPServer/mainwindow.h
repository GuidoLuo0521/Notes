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
    void on_btnSendPause_clicked();

    void on_textEdit_textChanged();

private:
    Ui::MainWindow *ui;

    int m_nPort = 5555;
    QUdpSocket * m_pUdpSocket;
};
#endif // MAINWINDOW_H
