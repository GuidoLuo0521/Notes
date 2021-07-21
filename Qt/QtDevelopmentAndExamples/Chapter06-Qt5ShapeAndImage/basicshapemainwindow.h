#ifndef BASICSHAPEMAINWINDOW_H
#define BASICSHAPEMAINWINDOW_H

#include <QMainWindow>
#include <QComboBox>
#include <QFrame>
#include <QSpinBox>
#include "paintareawidget.h"

namespace Ui {
class BasicShapeMainWindow;
}

class BasicShapeMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit BasicShapeMainWindow(QWidget *parent = nullptr);
    ~BasicShapeMainWindow();

private:
    Ui::BasicShapeMainWindow *ui;

private:
    void CreateWidgets();


private:
    PaintAreaWidget * m_pPaintAreaWidget;

    QComboBox * m_pComboBoxShape;
    QFrame * m_pFramePenColor;
    QSpinBox * m_pSpinBoxPenWidth;
    QComboBox * m_pComboBoxPenStyle;
    QComboBox * m_pComboBoxPenCapStyle;
    QComboBox * m_pComboBoxJoinStyle;
    QComboBox * m_pComboBoxFillRule;
    QComboBox * m_pComboBoxSpread;
    QFrame * m_pFrameBrushColor;
    QComboBox * m_pComboBoxBrushStyle;

signals:
    void ChangeShape(int shape);
    void ChangePenColor(QColor color);
    void ChangePenStyle(Qt::PenStyle style);
    void ChangePenCapStyle(Qt::PenCapStyle style);
    void ChangePenJoinStyle(Qt::PenJoinStyle style);
    void ChangeFillRule(Qt::FillRule rule);
    void ChangeSpread(QGradient::Spread spread);
    void ChangeBrushColor(QColor color);
    void ChangeBrushStyle(Qt::BrushStyle style);
    void ChangeTextFont(QFont font);



private slots:
    void OnChangedPenColor();
    void OnChangedPenStyle(int style);
    void OnChangedPenCapStyle(int style);
    void OnChangedPenJoinStyle(int style);
    void OnChangedFillRule(int rule);
    void OnChangedSpread(int gradient);
    void OnChangedBrushColor();
    void OnChangedBrushStyle(int style);
    void OnChangedTextFont();
};

#endif // BASICSHAPEMAINWINDOW_H
