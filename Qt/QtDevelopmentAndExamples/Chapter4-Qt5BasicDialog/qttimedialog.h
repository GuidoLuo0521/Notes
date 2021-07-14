#ifndef QTTIMEDIALOG_H
#define QTTIMEDIALOG_H


#include <QLCDNumber>

class QtTimeDialog : public QLCDNumber
{
    Q_OBJECT

public:
    explicit QtTimeDialog(QWidget *parent = nullptr);
    ~QtTimeDialog();

public:
    void mousePressEvent(QMouseEvent *);
    void mouseMoveEvent(QMouseEvent *);

public slots:
    void ShowTime();        // 显示当前的时间

private:
    QPoint m_DragPosition;  // 鼠标点相对于电子时钟窗体左上角的偏移值
    bool m_bShowColon;       // 是否显示 ":"

};

#endif // QTTIMEDIALOG_H
