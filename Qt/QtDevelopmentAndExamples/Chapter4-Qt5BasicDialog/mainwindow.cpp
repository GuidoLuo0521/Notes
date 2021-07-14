#include "mainwindow.h"
#include "qtprogress.h"
#include "qttoolbox.h"
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

    // 获取用户保存的用户名
    strFileName = QFileDialog::getSaveFileName();
    ui->leFilePath->setText(strFileName);

    // 获取用户选择的已存在的目录
    strFileName = QFileDialog::getExistingDirectory();
    ui->leFilePath->setText(strFileName);

    // 获取打开选择的文件名列表
    QStringList strList = QFileDialog::getOpenFileNames();


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

void MainWindow::on_btnInputDialog_clicked()
{
    QInputDialog::getText(nullptr, "Input Text", "get Text");

    QStringList listItem;
    listItem << "111" << "222" << "333" ;
    QInputDialog::getItem(nullptr, "Input Text", "get Item", listItem);

    QInputDialog::getInt(nullptr, "Input Text", "get Int");

    QInputDialog::getDouble(nullptr, "Input Text", "get Double");
}

void MainWindow::on_btnStdMsgDialog_clicked()
{
    QMessageBox::question( nullptr, "question", "question");
    QMessageBox::information( nullptr, "information", "information");
    QMessageBox::warning( nullptr, "warning", "warning");
    QMessageBox::critical( nullptr, "critical", "critical");

    QMessageBox::about( nullptr, "about", "about");
    QMessageBox::aboutQt(nullptr);
}

void MainWindow::on_btnCustomerMsgDialog_clicked()
{
    QMessageBox customMsgBox;
    customMsgBox.setWindowTitle("用户自定义消息对话框");

    customMsgBox.setText("用户自定义消息对话框 的提示信息");
    customMsgBox.setIconPixmap(QPixmap("F:\\lena-0.jpg"));

    customMsgBox.addButton(new QPushButton("确定"), QMessageBox::ActionRole );
    customMsgBox.addButton(new QPushButton("取消"), QMessageBox::ActionRole );

    customMsgBox.exec();

    QString strText = customMsgBox.clickedButton()->text();

    //ui->leCustomerMsg->setText(strText);

    if( customMsgBox.clickedButton()->text() == "确定" )
        ui->leCustomerMsg->setText("点击了确定");
    else if( customMsgBox.clickedButton()->text() == "取消" )
        ui->leCustomerMsg->setText("点击了取消");

}

void MainWindow::on_btnToolBox_clicked()
{
    #if 0
    // 这种就会一闪而过
    // 这样声明，存储在栈上， show 不会阻塞，所以继续执行
    // 所以，出去就销毁了，所以，你伤害了我，还一闪而过
    QtToolBox toolbox;
    toolbox.show();

#endif

    QtToolBox * pToolBox = new QtToolBox();
    pToolBox->show();
}

void MainWindow::on_btnProgress_clicked()
{
    QtProgress * pProgress = new QtProgress();
    pProgress->show();
}
