#include "qttoolbox.h"
#include "ui_qttoolbox.h"

#include <QToolBox>
#include <QToolButton>

#include <QGroupBox>
#include <QVBoxLayout>

QtToolBox::QtToolBox(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::QtToolBox)
{
    ui->setupUi(this);

    QVBoxLayout * pMainVBox = new QVBoxLayout();

    QToolBox * pToolBox = new QToolBox(this);

    QGroupBox * pMyFrient = new QGroupBox();
    QVBoxLayout *pMyFrientLayout = new QVBoxLayout(pMyFrient);

    QToolButton * pToolButton1 = new QToolButton();
    pToolButton1->setText("张三");
    pMyFrientLayout->addWidget(pToolButton1);

    QToolButton * pToolButton2 = new QToolButton();
    pToolButton2->setText("李四");
    pMyFrientLayout->addWidget(pToolButton2);


    QGroupBox * pSchoolFrientBox = new QGroupBox();
    QVBoxLayout *pSchoolFrientLayout = new QVBoxLayout(pSchoolFrientBox);

    QToolButton * pToolButton3 = new QToolButton();
    pToolButton3->setText("张三同学");
    pSchoolFrientLayout->addWidget(pToolButton3);

    QToolButton * pToolButton4 = new QToolButton();
    pToolButton4->setText("李四同学");
    pSchoolFrientLayout->addWidget(pToolButton4);


    pToolBox->addItem((QWidget*)pMyFrient, "我的好友");
    pToolBox->addItem((QWidget*)pSchoolFrientBox, "校友");


    pMainVBox->addWidget(pToolBox);

    this->setLayout(pMainVBox);

}

QtToolBox::~QtToolBox()
{
    delete ui;
}
