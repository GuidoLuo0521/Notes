#include "progressbarpage.h"
#include "ui_progressbarpage.h"

ProgressBarPage::ProgressBarPage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ProgressBarPage)
{
    ui->setupUi(this);

    ui->progressBar->setMaximum(0);
    ui->progressBar->setMinimum(0);
}

ProgressBarPage::~ProgressBarPage()
{
    delete ui;
}
