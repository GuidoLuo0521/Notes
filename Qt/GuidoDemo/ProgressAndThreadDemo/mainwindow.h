#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QEventLoop>

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
    void on_startDialogBtn_clicked();

    void on_starWidgetBtn_clicked();


private:
    Ui::MainWindow *ui;

    QEventLoop m_loop;
};
#endif // MAINWINDOW_H
