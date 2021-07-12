#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>

#include <QFileDialog>          // 文化对话框
#include <QColorDialog>         // 颜色对话框
#include <QFontDialog>          // 字体对话框
#include <QInputDialog>         // 输入对话框
#include <QMessageBox>          // 消息对话框


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

void MainWindow::InitLayout()
{

}


void MainWindow::on_btnFileDilog_clicked()
{
    QString strFileName = QFileDialog::getOpenFileName();

    ui->leFilePath->setText(strFileName);
}

void MainWindow::on_btnColorDialog_clicked()
{
    QColor color = QColorDialog::getColor();
    if( color.isValid() )
    {
        qDebug() << color;

        ui->frameColor->setFrameShape(QFrame::Box);

        // 当使用QPalette为窗口设定背景并使用QPalette::Window时
        // 必须调用setAutoFillBackground(true)!!!
        ui->frameColor->setAutoFillBackground(true);
        ui->frameColor->setPalette(QPalette(color));
    }
}

void MainWindow::on_btnFontDialog_clicked()
{
    bool ok = true;
    QFont font = QFontDialog::getFont( &ok);

    ui->lleStdFont->setFont(font);

}
