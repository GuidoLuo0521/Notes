#include "progresspage.h"
#include "ui_progresspage.h"

ProgressPage::ProgressPage(QDialog *parent) :
    QDialog(parent),
    ui(new Ui::ProgressPage)
{
    ui->setupUi(this);

    ui->progressBar->setMinimum(0);
    ui->progressBar->setMaximum(100);

    this->setWindowFlag(Qt::FramelessWindowHint);
}

ProgressPage::~ProgressPage()
{
    delete ui;
}

void ProgressPage::setValue(const int val)
{
    ui->progressBar->setValue(val);

    if(100 == val)
        close();
}
