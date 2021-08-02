#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->btnStop->setEnabled(false);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_btnStart_clicked()
{
    for( int i = 0; i < m_knThreadSize; ++i )
    {
        m_pArrThread[i] = new WorkThread();
        connect(m_pArrThread[i], SIGNAL(finished()), m_pArrThread[i], SLOT(deleteLater()));
    }

    for( int i = 0; i < m_knThreadSize; ++i )
    {
        m_pArrThread[i]->start();
    }

    ui->btnStart->setEnabled(false);
    ui->btnStop->setEnabled(true);
}

void MainWindow::on_btnStop_clicked()
{
    for( int i = 0; i < m_knThreadSize; ++i )
    {
        // 当然，线程都一样，不推荐使用 terminate(); 不安全。
        // 因为 线程可以在其代码路径中的任何一点终止。修改数据时可以终止线程。
        // 线程没有机会自行清理，解锁任何持有的互斥锁等。简而言之，只有在绝对必要时才使用此功能。
        m_pArrThread[i]->terminate();
        m_pArrThread[i]->wait();
    }

    ui->btnStop->setEnabled(false);
    ui->btnStart->setEnabled(true);


}
