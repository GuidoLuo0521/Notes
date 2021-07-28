#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QHostInfo>
#include <QNetworkInterface>

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


void MainWindow::on_btnLocalHost_clicked()
{
    ShowLocalHostInfo();

    QHostInfo info = QHostInfo::fromName("www.baidu.com");


    QList<QHostAddress>	addrlist = info.addresses();

    if( addrlist.isEmpty() == false )
    {
        ui->textEdit->append("www.baidu.com IPv4：" + addrlist.at(1).toString());
        ui->textEdit->append("www.baidu.com IPv6：" + addrlist.at(0).toString());
    }

}

void MainWindow::on_btnClearText_clicked()
{
    ui->textEdit->clear();
}

void MainWindow::ShowLocalHostInfo()
{
    /*
     * USER-20200628ZB
     * fe80::64c3:ab5a:5c79:8b5e%12
     * 192.168.1.131
    */

    // 获取主机的名称 ： USER-20200628ZB
    QString str = QHostInfo::localHostName();
    ui->textEdit->append("主机名（HostName）：" + str);

    // 从主机名获取主机的信息
    QHostInfo hostinfo = QHostInfo::fromName(str);

    // 获取主机地址 192.168.1.131
    QList<QHostAddress>	addrlist = hostinfo.addresses();

    if( addrlist.isEmpty() == false )
    {
        ui->textEdit->append("IPv4：" + addrlist.at(1).toString());
        ui->textEdit->append("IPv6：" + addrlist.at(0).toString());
    }
}


void MainWindow::on_btnDetail_clicked()
{
    ShowLocalDetial();
}

void MainWindow::ShowLocalDetial()
{
    QString detail = "";

    //获取所有网络接口的列表
    QList<QNetworkInterface> list = QNetworkInterface::allInterfaces();

    for ( int i = 0; i < list.count(); ++i) {

        QNetworkInterface interface = list.at(i);
        // 获得网络接口的名称
        ui->textEdit->append("设备：" + interface.name());
        // 获得网络接口的硬件地址
        ui->textEdit->append("硬件地址：" + interface.hardwareAddress());

        // 每个网络接口包含0个或者多个IP地址，每个IP地址有选择性的与一个子网掩码或者一个广播地址相关联。
        // QNetworkAddressEntry 类存储了被网络接口支持的一个IP地址，同时还包括与之相关的子网掩码和广播地址
        QList<QNetworkAddressEntry> entryList = interface.addressEntries();
        for ( int j = 0; j < entryList.count() ; ++j)
        {
            ui->textEdit->append("\tIP：" + entryList[j].ip().toString());
            ui->textEdit->append("\t子网掩码P：" + entryList[j].netmask().toString());
            ui->textEdit->append("\t广播地址：" + entryList[j].broadcast().toString());
        }
    }
}
