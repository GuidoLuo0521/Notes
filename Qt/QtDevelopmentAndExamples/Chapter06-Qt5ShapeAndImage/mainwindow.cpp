#include "mainwindow.h"
#include "positiondialog.h"
#include "ui_mainwindow.h"

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



void MainWindow::on_btnPosition_clicked()
{
    PositionDialog * pDlg = new PositionDialog;
    pDlg->setAttribute(Qt::WA_DeleteOnClose);

    pDlg->show();
}
