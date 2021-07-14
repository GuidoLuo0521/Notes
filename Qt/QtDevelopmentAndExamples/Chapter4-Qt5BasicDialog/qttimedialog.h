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
    void ShowTime();        // ��ʾ��ǰ��ʱ��

private:
    QPoint m_DragPosition;  // ��������ڵ���ʱ�Ӵ������Ͻǵ�ƫ��ֵ
    bool m_bShowColon;       // �Ƿ���ʾ ":"

};

#endif // QTTIMEDIALOG_H
