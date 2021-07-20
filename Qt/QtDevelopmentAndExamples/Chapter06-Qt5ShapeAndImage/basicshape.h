#ifndef BASICSHAPE_H
#define BASICSHAPE_H

#include <QMainWindow>

namespace Ui {
class BasicShape;
}

class BasicShape : public QMainWindow
{
    Q_OBJECT

public:
    explicit BasicShape(QWidget *parent = nullptr);
    ~BasicShape();

private:
    Ui::BasicShape *ui;
};

#endif // BASICSHAPE_H
