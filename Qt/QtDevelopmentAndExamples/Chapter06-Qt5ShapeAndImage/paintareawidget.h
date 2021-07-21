#ifndef PAINTAREAWIDGET_H
#define PAINTAREAWIDGET_H

#include <QMouseEvent>
#include <QPainter>
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
        NormalBrush,
        PixmapBrush
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
    void ChangeDrawText(QString text);
    void ChangeTextFont(QFont font);

    void ClearScreen();

protected:
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void paintEvent(QPaintEvent *event) override;

private:
    void UpDateAttribute();
    void DrawLine(QPainter &painter);
    void DrawRectangle(QPainter &painter);
    void DrawPolygon(QPainter &painter);
    void DrawPolyline(QPainter &painter);
    void DrawPoints(QPainter &painter);
    void DrawArc(QPainter &painter);
    void DrawText(QPainter &painter);

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

    QVector<QPoint> m_vLinesPoint;
    QString m_strAttribute;
    QPointF m_CurrentPoint, m_LastPoint;
    bool  m_bMousePressing;

    QString m_strText;
    QFont m_Font;



};

#endif // PAINTAREAWIDGET_H
