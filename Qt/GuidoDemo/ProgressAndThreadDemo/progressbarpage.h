#ifndef PROGRESSBARPAGE_H
#define PROGRESSBARPAGE_H

#include <QWidget>

namespace Ui {
class ProgressBarPage;
}

class ProgressBarPage : public QWidget
{
    Q_OBJECT

public:
    explicit ProgressBarPage(QWidget *parent = nullptr);
    ~ProgressBarPage();

private:
    Ui::ProgressBarPage *ui;
};

#endif // PROGRESSBARPAGE_H
