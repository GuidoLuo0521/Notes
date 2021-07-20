#include "paintareawidget.h"

PaintAreaWidget::PaintAreaWidget(QWidget *parent) : QWidget(parent)
{
    setAutoFillBackground(true);

    QPalette pltPen;
    pltPen.setColor(QPalette::Window, QColor(Qt::GlobalColor::white));
    this->setPalette(pltPen);
}

void PaintAreaWidget::ChangeShape(int shape)
{
    m_Shape = (PaintAreaWidget::Shape)shape;
}

void PaintAreaWidget::ChangePenColor(QColor color)
{
    m_PenColor = color;
}

void PaintAreaWidget::ChangePenWidth(int width)
{
    m_PenWidth = width;
}

void PaintAreaWidget::ChangePenStyle(Qt::PenStyle style)
{
    m_PenStyle = style;
}

void PaintAreaWidget::ChangePenCapStyle(Qt::PenCapStyle style)
{
    m_PenCapStyle = style;
}

void PaintAreaWidget::ChangePenJoinStyle(Qt::PenJoinStyle style)
{
    m_PenJoinStyle = style;
}

void PaintAreaWidget::ChangeFillRule(Qt::FillRule rule)
{
    m_FillRule = rule;
}

void PaintAreaWidget::ChangeSpread(QGradient::Spread spread)
{
    m_Spread = spread;
}

void PaintAreaWidget::ChangeBrushColor(QColor color)
{
    m_BrushColor = color;
}

void PaintAreaWidget::ChangeBrushStyle(Qt::BrushStyle style)
{
    m_BrushStyle = style;
}
