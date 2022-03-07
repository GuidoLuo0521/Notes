#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "workerthread.h"
#include "progresspage.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_startBtn_clicked()
{
    ProgressPage * page = new ProgressPage;
    page->setModal(true);

    QObject obj;
    WorkerThread * thread = new WorkerThread;

    connect( thread, SIGNAL(sigProgress(const int )), page, SLOT(setValue(const int )));
    connect( thread, SIGNAL(finished()), thread, SLOT(deleteLater()));


    thread->start();

    page->showNormal();
}
