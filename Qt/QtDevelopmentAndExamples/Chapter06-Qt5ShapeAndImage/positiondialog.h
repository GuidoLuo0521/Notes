#ifndef POSTIONDIALOG_H
#define POSTIONDIALOG_H

#include <QMainWindow>
#include <QTextEdit>

namespace Ui {
class PositionDialog;
}

class PositionDialog : public QMainWindow
{
    Q_OBJECT

public:
    explicit PositionDialog(QWidget *parent = nullptr);
    ~PositionDialog();

protected:
    void moveEvent(QMoveEvent*) override;

private:
    void UpdateData();

private:
    Ui::PositionDialog *ui;

    QTextEdit * m_pTextEdit;
};

#endif // POSTIONDIALOG_H
