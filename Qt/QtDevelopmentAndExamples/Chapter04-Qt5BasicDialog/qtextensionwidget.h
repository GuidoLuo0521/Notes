#ifndef EXTENSIONWIDGET_H
#define EXTENSIONWIDGET_H

#include <QGridLayout>
#include <QWidget>
#include <QVBoxLayout>

namespace Ui {
class ExtensionWidget;
}

class QtExtensionWidget : public QWidget
{
    Q_OBJECT

public:
    explicit QtExtensionWidget(QWidget *parent = nullptr);
    ~QtExtensionWidget();

private:
    Ui::ExtensionWidget *ui;


private:
    void CreateBaseWidget();
    void CreateExtenWidget();

    QWidget * m_pBaseWidget;
    QWidget * m_pExtenWidget;


private:
    void ShowDetial();

};

#endif // EXTENSIONWIDGET_H
