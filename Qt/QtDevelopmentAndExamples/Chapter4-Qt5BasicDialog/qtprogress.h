#ifndef QTPROGRESS_H
#define QTPROGRESS_H

#include <QWidget>

namespace Ui {
class QtProgress;
}

class QtProgress : public QWidget
{
    Q_OBJECT

public:
    explicit QtProgress(QWidget *parent = nullptr);
    ~QtProgress();

private slots:
    void on_pushButton_clicked();

private:
    Ui::QtProgress *ui;
};

#endif // QTPROGRESS_H
