#include "qtprogress.h"
#include "ui_qtprogress.h"

#include <QProgressDialog>
#include <QPalette>

QtProgress::QtProgress(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::QtProgress)
{
    ui->setupUi(this);

    ui->comboBox->insertItem(0, "对话框");
    ui->comboBox->insertItem(1, "进度条");

    ui->lineEdit->setText("1000");

    ui->progressBar->setValue(0);

//    QPalette palette;
//    ui->progressBar->setPalette(palette);

}

QtProgress::~QtProgress()
{
    delete ui;
}

void QtProgress::on_pushButton_clicked()
{
    int nNum =ui->lineEdit->text().toUInt();
    ui->progressBar->setRange(0, nNum);
    ui->progressBar->setValue(0);

    if(ui->comboBox->currentIndex() == 1)
    {
        for(int i = 1; i <= nNum; ++i)
        {
            ui->progressBar->setValue(i);
            _sleep(10);
        }
    }
    else
    {
        QProgressDialog * pDlg  = new QProgressDialog(this);

        pDlg->setWindowModality(Qt::WindowModal);   // 模态显示
        pDlg->setMinimumDuration(10000);            // 设置低于 5 ms 就不显示对话框
        pDlg->setWindowTitle("Please Wait");
        pDlg->setLabelText("Copying...");
        pDlg->setCancelButtonText("Cancle");

        pDlg->setRange(0, nNum);

        for(int i = 1; i <= nNum; ++i)
        {
            if( pDlg->wasCanceled() )
                break;

            pDlg->setValue(i);
            _sleep(10);
        }
    }
}
