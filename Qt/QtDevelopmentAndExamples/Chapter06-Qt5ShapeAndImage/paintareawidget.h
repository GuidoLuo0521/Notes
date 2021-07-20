#ifndef PAINTAREAWIDGET_H
#define PAINTAREAWIDGET_H

#include <QWidget>


class PaintAreaWidget : public QWidget
{
    Q_OBJECT

public:
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

public:
    explicit PaintAreaWidget(QWidget *parent = nullptr);

signals:

public slots:
    void ChangeShape(int shape);
    void ChangePenColor(QColor color);
    void ChangePenWidth(int width);
    void ChangePenStyle(Qt::PenStyle style);
    void ChangePenCapStyle(Qt::PenCapStyle style);
    void ChangePenJoinStyle(Qt::PenJoinStyle style);
    void ChangeFillRule(Qt::FillRule rule);
    void ChangeSpread(QGradient::Spread gradient);
    void ChangeBrushColor(QColor color);
    void ChangeBrushStyle(Qt::BrushStyle style);

private:
    Shape  m_Shape = Line;
    QColor  m_PenColor = Qt::GlobalColor::black;
    int  m_PenWidth = 1;
    Qt::PenStyle  m_PenStyle = Qt::PenStyle::SolidLine;
    Qt::PenCapStyle  m_PenCapStyle = Qt::PenCapStyle::RoundCap;
    Qt::PenJoinStyle  m_PenJoinStyle = Qt::PenJoinStyle::BevelJoin;
    Qt::FillRule m_FillRule = Qt::FillRule::OddEvenFill;
    QGradient::Spread  m_Spread = QGradient::Spread::PadSpread;
    QColor  m_BrushColor = Qt::GlobalColor::black;
    Qt::BrushStyle  m_BrushStyle = Qt::BrushStyle::SolidPattern;

};

#endif // PAINTAREAWIDGET_H
