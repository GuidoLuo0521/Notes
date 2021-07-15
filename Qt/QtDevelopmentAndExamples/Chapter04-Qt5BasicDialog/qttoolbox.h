#ifndef QTTOOLBOX_H
#define QTTOOLBOX_H

#include <QWidget>

namespace Ui {
class QtToolBox;
}

class QtToolBox : public QWidget
{
    Q_OBJECT

public:
    explicit QtToolBox(QWidget *parent = nullptr);
    ~QtToolBox();

private:
    Ui::QtToolBox *ui;
};

#endif // QTTOOLBOX_H
