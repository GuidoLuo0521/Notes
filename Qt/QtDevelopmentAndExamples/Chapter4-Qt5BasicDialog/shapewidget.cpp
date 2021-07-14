#include "shapewidget.h"
#include "ui_shapewidget.h"

#include <QBitmap>
#include <QPainter>

static QString gs_FilePath = "d:\\11.png";

ShapeWidget::ShapeWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ShapeWidget)
{
    ui->setupUi(this);

    QPixmap pix;
    pix.load( gs_FilePath, 0, Qt::AvoidDither | Qt::ThresholdDither | Qt::ThresholdAlphaDither);
    resize(pix.size());
    setMask(QBitmap(pix));

}

ShapeWidget::~ShapeWidget()
{
    delete ui;
}

void ShapeWidget::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.drawPixmap(0, 0, QPixmap(gs_FilePath));
}

void ShapeWidget::mousePressEvent(QMouseEvent * event)
{
    if(event->button() == Qt::LeftButton)
    {
        // 求出窗口移动之前的坐标
        m_DragPosition = event->globalPos() - frameGeometry().topLeft();
        event->accept();
    }
    if(event->button()==Qt::RightButton)
    {
        close();
    }
}

void ShapeWidget::mouseMoveEvent(QMouseEvent * event)
{
    if(event->buttons()&Qt::LeftButton)
    {
        // 给出的坐标信息是相对于桌面的，即以桌面左上角为原点
        move(event->globalPos() - m_DragPosition);
        event->accept();
    }
}
