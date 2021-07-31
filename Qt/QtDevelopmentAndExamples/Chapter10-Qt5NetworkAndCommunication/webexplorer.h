#ifndef WEBEXPLORER_H
#define WEBEXPLORER_H

#include <QMainWindow>

#include <QNetworkReply>
#include <QNetworkRequest>
#include <QNetworkAccessManager>

namespace Ui {
class WebExplorer;
}

class WebExplorer : public QMainWindow
{
    Q_OBJECT

public:
    explicit WebExplorer(QWidget *parent = nullptr);
    ~WebExplorer();

private:
    Ui::WebExplorer *ui;

private slots:
    void ReplyFinished(QNetworkReply * p);

private:
    QNetworkAccessManager * m_pNetworkAccessManager;
};

#endif // WEBEXPLORER_H
