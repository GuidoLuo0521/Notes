#include "positiondialog.h"
#include "ui_positiondialog.h"

PositionDialog::PositionDialog(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::PositionDialog)
{
    ui->setupUi(this);

    m_pTextEdit = new QTextEdit();
    this->m_pTextEdit->setFontPointSize(30);
    this->setCentralWidget(m_pTextEdit);
}

PositionDialog::~PositionDialog()
{
    delete ui;
}

void PositionDialog::moveEvent(QMoveEvent *)
{
    UpdateData();
}

void PositionDialog::UpdateData()
{
    QString str = QString("x = %1 y = %2 \n"
                          "pos(%3,%4) \n"
                          "geometry(%5, %6) \n"
                          "rect(%7,%8,%9,%10) \n"
                          "size(%11,%12) \n"
                          "frameGeometry(%13,%14) \n")
                      .arg(this->x()).arg(this->y())
                      .arg(this->pos().x()).arg(this->pos().y())
                      .arg(this->geometry().x()).arg(this->geometry().y())
                      .arg(this->rect().left()).arg(this->rect().top()).arg(this->rect().right()).arg(this->rect().bottom())
                      .arg(this->size().width()).arg(this->size().height())
                      .arg(this->frameGeometry().width()).arg(this->frameGeometry().height());

    this->m_pTextEdit->setText(str);

}
