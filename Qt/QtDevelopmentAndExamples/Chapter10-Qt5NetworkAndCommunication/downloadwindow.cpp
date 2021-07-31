#include "downloadwindow.h"
#include "ui_downloadwindow.h"

#include <QFileInfo>
#include <QMessageBox>
#include <QFileDialog>
#include <QHttpPart>

DownLoadWindow::DownLoadWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::DownLoadWindow)
{
    ui->setupUi(this);
    ui->progressBar->setRange(0, 100);
    ui->progressBar->setValue(0);

    QString strUrl = "https://dldir1.qq.com/weixin/Windows/WeChatSetup.exe";
    ui->lineEdit->setText(strUrl);

    //QString strUrl = "http://www.millet.fun/file";

    m_pNetworkAccessManager = new QNetworkAccessManager(this);
}

DownLoadWindow::~DownLoadWindow()
{
    delete ui;
}

void DownLoadWindow::StartRequest(QUrl url, bool bGet)
{
    m_bGet = bGet;
    if(bGet)
    {
        m_pReply = m_pNetworkAccessManager->get(QNetworkRequest(url));
        connect( m_pReply, SIGNAL(downloadProgress(qint64, qint64)), this, SLOT(UpdateProgress(qint64, qint64)));
    }
    else
    {
        QString xlname = "text.xlsx";
        QHttpMultiPart *multiPart = new QHttpMultiPart(QHttpMultiPart::FormDataType);
        QHttpPart imagePart;
        imagePart.setHeader(QNetworkRequest::ContentTypeHeader, QVariant("text/xlsx"));
        imagePart.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant("form-data; name=\"file\"; filename=\""+ xlname + "\"")); // file为后端定义的key，filename即为excel文件名

        imagePart.setBodyDevice(m_pFile);
        m_pFile->setParent(multiPart);
        multiPart->append(imagePart);

        QNetworkRequest networkRequest(url);
        m_pReply = m_pNetworkAccessManager->post(networkRequest, multiPart);
        connect( m_pReply, SIGNAL(uploadProgress(qint64, qint64)), this, SLOT(UpdateProgress(qint64, qint64)));
    }

    connect( m_pReply, SIGNAL(readyRead()), this, SLOT(HttpReadyRead()));
    connect( m_pReply, SIGNAL(finished()), this, SLOT(HttpFinished()));
}

void DownLoadWindow::HttpFinished()
{
    m_pReply->deleteLater();
    m_pReply = nullptr;

    m_pFile->flush();
    m_pFile->close();

    delete m_pFile;
    m_pFile = nullptr;

    if(m_bGet)
        QMessageBox::information(this, "提示", "下载完成");
    else
        QMessageBox::information(this, "提示", "上传成功");

}

void DownLoadWindow::HttpReadyRead()
{
    if( m_pFile )
    {
        m_pFile->write(m_pReply->readAll());
    }
}

void DownLoadWindow::UpdateProgress(qint64 bytesReceived, qint64 bytesTotal)
{
    ui->progressBar->setMaximum(bytesTotal);
    ui->progressBar->setValue(bytesReceived);
}

void DownLoadWindow::on_btnDownLoad_clicked()
{
    m_Url = ui->lineEdit->text();
    QFileInfo info(m_Url.path());

    QString fileName(info.fileName());
    QString strDir = "D:/"+fileName;
    QString strFileName = QFileDialog::getSaveFileName(this, "保存文件", strDir);

    if(strFileName == "")
        return;

    m_pFile = new QFile(strFileName);
    if(m_pFile->open(QIODevice::WriteOnly) == false)
    {
        QMessageBox::critical(this, "错误", m_pFile->errorString());

        delete  m_pFile;
        m_pFile = nullptr;
        return;
    }

    StartRequest(QUrl(m_Url), true);
}

void DownLoadWindow::on_btnUpLoad_clicked()
{
    m_Url = ui->lineEdit->text();

    QString strDir = "D:/";
    QString strFileName = QFileDialog::getOpenFileName(this, "选择文件", strDir);

    if(strFileName == "")
        return;

    m_pFile = new QFile(strFileName);

    if(m_pFile->open(QIODevice::ReadOnly) == false)
    {
        QMessageBox::critical(this, "错误", m_pFile->errorString());

        delete  m_pFile;
        m_pFile = nullptr;
        return;
    }

    StartRequest(QUrl(m_Url), false);
}
