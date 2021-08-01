#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QLabel>
#include <QMainWindow>
#include <QMouseEvent>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    bool eventFilter(QObject *, QEvent *);

protected:
    virtual void paintEvent(QPaintEvent *event) override;

    virtual void mousePressEvent(QMouseEvent *event) override;
    virtual void mouseMoveEvent(QMouseEvent *event) override;

    virtual void keyPressEvent(QKeyEvent *event) override;
    virtual void keyReleaseEvent(QKeyEvent *event) override;

private:
    Ui::MainWindow *ui;

    QPixmap m_LeftPixmap;
    QPixmap m_CenterPixmap;
    QPixmap m_RightPixmap;

    QPixmap m_Pixmap;
    int m_PixmapX = 0, m_PixmapY = 0;

    QLabel * m_pCrntMousePos;
    QLabel * m_pLeftMousePos;
    QLabel * m_pRightMousePos;

    QLabel * m_pLeftLable;
    QLabel * m_pCenterLable;
    QLabel * m_pRightLable;

};
#endif // MAINWINDOW_H
