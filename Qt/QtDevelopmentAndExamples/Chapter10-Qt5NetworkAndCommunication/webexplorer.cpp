#include "webexplorer.h"
#include "ui_webexplorer.h"

WebExplorer::WebExplorer(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::WebExplorer)
{
    ui->setupUi(this);
    m_pNetworkAccessManager = new QNetworkAccessManager(this);
    connect( m_pNetworkAccessManager, SIGNAL(finished(QNetworkReply *)), this, SLOT(ReplyFinished(QNetworkReply *)));

    m_pNetworkAccessManager->get(QNetworkRequest(QUrl("https://www.zhihu.com/question/459653716")));
    //m_pNetworkAccessManager->get(QNetworkRequest(QUrl("http://www.baidu.com")));
    //m_pNetworkAccessManager->get(QNetworkRequest(QUrl("http://www.millet.fun/test.html")));
    //m_pNetworkAccessManager->get(QNetworkRequest(QUrl("http://www.millet.fun")));
    //m_pNetworkAccessManager->get(QNetworkRequest(QUrl("https://www.baidu.com")));
    //m_pNetworkAccessManager->get(QNetworkRequest(QUrl("https://translate.google.cn/?sl=en&tl=zh-CN&text=sended&op=translate")));
    m_pNetworkAccessManager->get(QNetworkRequest(QUrl("https://blog.csdn.net/xqhrs232/article/details/82427842")));

}

WebExplorer::~WebExplorer()
{
    delete ui;
}

void WebExplorer::ReplyFinished(QNetworkReply *p)
{
    QString str = p->readAll();
    ui->textEdit->setHtml(str);
    p->deleteLater();
}
