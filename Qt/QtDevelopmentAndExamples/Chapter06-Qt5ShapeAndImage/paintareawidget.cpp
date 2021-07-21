#include "paintareawidget.h"

#include <QLineEdit>
#include <QTextLine>

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
    m_vLinesPoint.clear();
    update();
}

void PaintAreaWidget::ChangePenColor(QColor color)
{
    m_PenColor = color;
    //m_vLinesPoint.clear();
    update();
}

void PaintAreaWidget::ChangePenWidth(int width)
{
    m_PenWidth = width;
    //m_vLinesPoint.clear();
    update();
}

void PaintAreaWidget::ChangePenStyle(Qt::PenStyle style)
{
    m_PenStyle = style;
    //m_vLinesPoint.clear();
    update();
}

void PaintAreaWidget::ChangePenCapStyle(Qt::PenCapStyle style)
{
    m_PenCapStyle = style;
    //m_vLinesPoint.clear();
    update();
}

void PaintAreaWidget::ChangePenJoinStyle(Qt::PenJoinStyle style)
{
    m_PenJoinStyle = style;
    //m_vLinesPoint.clear();
    update();
}

void PaintAreaWidget::ChangeFillRule(Qt::FillRule rule)
{
    m_FillRule = rule;
    //m_vLinesPoint.clear();
    update();
}

void PaintAreaWidget::ChangeSpread(QGradient::Spread spread)
{
    m_Spread = spread;
    //m_vLinesPoint.clear();
    update();
}

void PaintAreaWidget::ChangeBrushColor(QColor color)
{
    m_BrushColor = color;
    //m_vLinesPoint.clear();
    update();
}

void PaintAreaWidget::ChangeBrushStyle(Qt::BrushStyle style)
{
    m_BrushStyle = style;
    //m_vLinesPoint.clear();
    update();
}

void PaintAreaWidget::ChangeDrawText(QString text)
{
    m_strText = text;
    update();
}

void PaintAreaWidget::ChangeTextFont(QFont font)
{
    m_Font = font;
    update();
}

void PaintAreaWidget::ClearScreen()
{
    m_vLinesPoint.clear();
    update();
}

void PaintAreaWidget::mousePressEvent(QMouseEvent *event)
{
    m_bMousePressing  = true;
    m_CurrentPoint = event->pos();
    m_vLinesPoint.push_back(event->pos());

    update();
}

void PaintAreaWidget::mouseMoveEvent(QMouseEvent *event)
{
    if( m_bMousePressing )
    {
        m_LastPoint = event->pos();
        m_vLinesPoint.push_back(event->pos());
        update();
    }
}

void PaintAreaWidget::mouseReleaseEvent(QMouseEvent *event)
{
    m_LastPoint = event->pos();
    m_vLinesPoint.push_back(event->pos());
    m_bMousePressing  = false;

    update();
}

void PaintAreaWidget::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    /*
    enum Shape {
        Line,
        Rectangle,
        RoundRect,
        Ellipse,
        Polygon,
        Polyline,
        Points,
        Arc,
        Path,
        Text,
        Pixmap
    };
*/
    QBrush brush( m_BrushColor);
    painter.setBrush(brush);
    if(m_BrushStyle == Qt::TexturePattern)
        brush.setTexture(QPixmap("cup.bmp"));
    if(m_BrushStyle == Qt::LinearGradientPattern )
    {
        QLinearGradient conicalGradient(0, 0, 400, 400);
        conicalGradient.setColorAt(0.0, Qt::white);
        conicalGradient.setColorAt(0.2, Qt::cyan);
        conicalGradient.setColorAt(1.0, Qt::black);
        conicalGradient.setSpread(m_Spread);
        painter.setBrush(conicalGradient);
    }
    if(m_BrushStyle == Qt::RadialGradientPattern)
    {
        QRadialGradient conicalGradient(200, 200, 150, 150, 100);
        conicalGradient.setColorAt(0.0, Qt::white);
        conicalGradient.setColorAt(0.2, Qt::cyan);
        conicalGradient.setColorAt(1.0, Qt::black);
        conicalGradient.setSpread(m_Spread);
        painter.setBrush(conicalGradient);
    }
    if(m_BrushStyle == Qt::ConicalGradientPattern)
    {
        QConicalGradient conicalGradient(QPointF(350, 190), 60);
        conicalGradient.setColorAt(0.2, Qt::cyan);
        conicalGradient.setColorAt(0.9, Qt::black);
        painter.setBrush(conicalGradient);
    }


    if(m_Shape == Shape::Line || m_Shape == Shape::Path)
        DrawLine(painter);
    if(m_Shape == Shape::Rectangle || m_Shape == Shape::RoundRect || m_Shape == Shape::Ellipse )
        DrawRectangle(painter);
    if( m_Shape == Shape::Polygon)
        DrawPolygon(painter);
    if( m_Shape == Shape::Polyline )
        DrawPolyline(painter);
    if( m_Shape == Shape::Points )
        DrawPoints(painter);
    if( m_Shape == Shape::Arc )
        DrawArc(painter);
    if( m_Shape == Shape::Text )
        DrawText(painter);

}

void PaintAreaWidget::UpDateAttribute()
{

}

void PaintAreaWidget::DrawLine(QPainter& painter)
{
    QPen pen( m_PenColor, m_PenWidth, m_PenStyle, m_PenCapStyle, m_PenJoinStyle);
    painter.setPen(pen);
    if( m_PenJoinStyle == Qt::PenJoinStyle::MiterJoin)
        painter.drawLine(m_LastPoint, m_CurrentPoint);
    else
    {
        QPainterPath path;

        QPolygon polygon(m_vLinesPoint);
        path.addPolygon(polygon);

        painter.drawPath(path);

    }
}

void PaintAreaWidget::DrawRectangle(QPainter &painter)
{
    if( m_vLinesPoint.size() < 2)
        return;

    QPen pen( m_PenColor, m_PenWidth, m_PenStyle, m_PenCapStyle, m_PenJoinStyle);
    painter.setPen(pen);

    int nSize = m_vLinesPoint.size();

    if( m_Shape == Shape::Rectangle)
    {
        painter.drawRect(
            m_vLinesPoint[0].x(),
            m_vLinesPoint[0].y(),
            m_vLinesPoint[nSize - 1].x() - m_vLinesPoint[0].x(),
            m_vLinesPoint[nSize - 1].y() - m_vLinesPoint[0].y());
    }
    else if(m_Shape == Shape::RoundRect)
    {
        painter.drawRoundedRect(
            m_vLinesPoint[0].x(),
            m_vLinesPoint[0].y(),
            m_vLinesPoint[nSize - 1].x() - m_vLinesPoint[0].x(),
            m_vLinesPoint[nSize - 1].y() - m_vLinesPoint[0].y(),
            25,
            25);
    }
    else if(m_Shape == Shape::Ellipse)
    {
        painter.drawEllipse(
            m_vLinesPoint[0].x(),
            m_vLinesPoint[0].y(),
            m_vLinesPoint[nSize - 1].x() - m_vLinesPoint[0].x(),
            m_vLinesPoint[nSize - 1].y() - m_vLinesPoint[0].y());
    }
}

void PaintAreaWidget::DrawPolygon(QPainter &painter)
{
    QPen pen( m_PenColor, m_PenWidth, m_PenStyle, m_PenCapStyle, m_PenJoinStyle);
    painter.setPen(pen);

    painter.drawPolygon(m_vLinesPoint,  m_FillRule);
}

void PaintAreaWidget::DrawPolyline(QPainter &painter)
{
    QPen pen( m_PenColor, m_PenWidth, m_PenStyle, m_PenCapStyle, m_PenJoinStyle);
    painter.setPen(pen);

    painter.drawPolyline(m_vLinesPoint);
}

void PaintAreaWidget::DrawPoints(QPainter &painter)
{
    QPen pen( m_PenColor, m_PenWidth, m_PenStyle, m_PenCapStyle, m_PenJoinStyle);
    painter.setPen(pen);

    painter.drawPoints(m_vLinesPoint);
}

void PaintAreaWidget::DrawArc(QPainter &painter)
{
    if( m_vLinesPoint.size() < 2)
        return;

    // pen 可放到 change 中
    QPen pen( m_PenColor, m_PenWidth, m_PenStyle, m_PenCapStyle, m_PenJoinStyle);
    painter.setPen(pen);

    int nSize = m_vLinesPoint.size();

    /*
     * The startAngle and spanAngle must be specified in 1/16th of a degree, i.e. a full circle equals 5760 (16 * 360).
     * Positive values for the angles mean counter-clockwise while negative values mean the clockwise direction.
     * Zero degrees is at the 3 o'clock position.
    */
    painter.drawArc(
        m_vLinesPoint[0].x(),
        m_vLinesPoint[0].y(),
        m_vLinesPoint[nSize - 1].x() - m_vLinesPoint[0].x(),
        m_vLinesPoint[nSize - 1].y() - m_vLinesPoint[0].y(),
        15 * 16,
        135 * 16);
}

void PaintAreaWidget::DrawText(QPainter &painter)
{
    if( m_vLinesPoint.size() < 1)
        return;

    int nSize = m_vLinesPoint.size();
    painter.setFont(m_Font);
    painter.drawText( m_vLinesPoint[nSize - 1], m_strText);
}




