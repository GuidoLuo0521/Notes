#ifndef DOWNLOADWINDOW_H
#define DOWNLOADWINDOW_H

#include <QMainWindow>

#include <QFile>
#include <QUrl>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QNetworkAccessManager>

namespace Ui {
class DownLoadWindow;
}

class DownLoadWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit DownLoadWindow(QWidget *parent = nullptr);
    ~DownLoadWindow();

    // bGet true:get  false:post
    void StartRequest(QUrl url, bool bGet);

private slots:
    void HttpFinished();
    void HttpReadyRead();
    void UpdateProgress(qint64 bytesReceived, qint64 bytesTotal);

private slots:
    void on_btnDownLoad_clicked();

    void on_btnUpLoad_clicked();

private:
    bool m_bGet;
    Ui::DownLoadWindow *ui;
    QNetworkAccessManager * m_pNetworkAccessManager;
    QNetworkReply * m_pReply;
    QUrl m_Url;
    QFile * m_pFile;
};

#endif // DOWNLOADWINDOW_H
