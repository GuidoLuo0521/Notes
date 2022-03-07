#ifndef PROGRESSPAGE_H
#define PROGRESSPAGE_H

#include <QDialog>

namespace Ui {
class ProgressPage;
}

class ProgressPage : public QDialog
{
    Q_OBJECT

public:
    explicit ProgressPage(QDialog *parent = nullptr);
    ~ProgressPage();


public slots:
    void setValue(const int val);

private:
    Ui::ProgressPage *ui;
};

#endif // PROGRESSPAGE_H
