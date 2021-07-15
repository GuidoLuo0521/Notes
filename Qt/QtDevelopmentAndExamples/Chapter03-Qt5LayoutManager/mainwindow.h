#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

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
    void on_btnSplitter_clicked();

    void on_btnDock_clicked();

    void on_btnStacked_clicked();

    void on_btnRead_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
