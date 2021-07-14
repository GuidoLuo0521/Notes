#ifndef SHAPEWIDGET_H
#define SHAPEWIDGET_H

#include <QMouseEvent>
#include <QWidget>

namespace Ui {
class ShapeWidget;
}

class ShapeWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ShapeWidget(QWidget *parent = nullptr);
    ~ShapeWidget();

protected:
    void paintEvent(QPaintEvent *event) override;
    void mousePressEvent(QMouseEvent *) override;
    void mouseMoveEvent(QMouseEvent *) override;

    QPoint m_DragPosition;

private:
    Ui::ShapeWidget *ui;
};

#endif // SHAPEWIDGET_H
