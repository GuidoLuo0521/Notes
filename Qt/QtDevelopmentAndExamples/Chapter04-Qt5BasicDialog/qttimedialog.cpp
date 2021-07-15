#include "qttimedialog.h"

#include <QMouseEvent>
#include <QTime>
#include <QTimer>
#include <QDebug>

QtTimeDialog::QtTimeDialog(QWidget *parent) :
    QLCDNumber(parent)
{
    QPalette p=palette();
    p.setColor(QPalette::Window, Qt::blue);
    setPalette(p);

    setWindowFlags(Qt::FramelessWindowHint);
    setDigitCount(8);       // �����λ��Ҫ���ã�Ҫ��Ȼ��ʾ����ȷ
    setWindowOpacity(0.8);

    QTimer *timer = new QTimer(this);
    connect(timer , SIGNAL(timeout()) , this , SLOT(ShowTime()));
    timer->start(1000);
    ShowTime();
    resize(230,50);
    m_bShowColon = true;
}

QtTimeDialog::~QtTimeDialog()
{

}

void QtTimeDialog::mousePressEvent(QMouseEvent * event)
{
    if(event->button() == Qt::LeftButton)
    {
        // ��������ƶ�֮ǰ������
        m_DragPosition = event->globalPos() - frameGeometry().topLeft();
        event->accept();
    }
    if(event->button()==Qt::RightButton)
    {
        close();
    }
}

void QtTimeDialog::mouseMoveEvent(QMouseEvent * event)
{
    if(event->buttons()&Qt::LeftButton)
    {
        // ������������Ϣ�����������ģ������������Ͻ�Ϊԭ��
        move(event->globalPos() - m_DragPosition);
        event->accept();
    }
}

void QtTimeDialog::ShowTime()
{
    QTime time = QTime::currentTime();
    QString text = time.toString("hh:mm:ss");

    text[2]= m_bShowColon ? ':' : ' ';
    text[5]= m_bShowColon ? ':' : ' ';
    m_bShowColon = !m_bShowColon;

    qDebug() << text;
    display(text);
    display(QTime::currentTime().toString("hh:mm:ss"));
}
