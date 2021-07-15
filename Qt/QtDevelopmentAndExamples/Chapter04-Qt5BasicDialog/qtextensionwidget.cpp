#include "qtextensionwidget.h"
#include "ui_qtextensionwidget.h"

#include <QHBoxLayout>
#include <QGridLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QComboBox>

QtExtensionWidget::QtExtensionWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ExtensionWidget)
{
    ui->setupUi(this);

    CreateBaseWidget();
    CreateExtenWidget();

    QVBoxLayout * pMainLayout = new QVBoxLayout();
    pMainLayout->addWidget(m_pBaseWidget);
    pMainLayout->addWidget(m_pExtenWidget);

    // 设置固定尺寸，这样才能不改变位置。默认自适应
    pMainLayout->setSizeConstraint(QLayout::SetFixedSize);

    // 默认隐藏
    m_pExtenWidget->setHidden(true);
    this->setLayout(pMainLayout);

}

QtExtensionWidget::~QtExtensionWidget()
{
    delete ui;
}

void QtExtensionWidget::CreateBaseWidget()
{
    m_pBaseWidget = new QWidget;
    QGridLayout * pGridLayoutBase = new QGridLayout();

    QLabel * plbName = new QLabel("Name:");
    QLineEdit * pLineEdit = new QLineEdit("Guido");
    QPushButton * pbtnOk = new QPushButton("Ok");

    pGridLayoutBase->addWidget(plbName, 0, 0);
    pGridLayoutBase->addWidget(pLineEdit, 0, 1);
    pGridLayoutBase->addWidget(pbtnOk, 0, 2);

    QLabel * plbSex = new QLabel("Sex:");
    QComboBox * pComboBox = new QComboBox();
    pComboBox->addItem("M");
    pComboBox->addItem("F");


    QPushButton * pbtnDetial = new QPushButton("Detial");
    pGridLayoutBase->addWidget(plbSex, 1, 0);
    pGridLayoutBase->addWidget(pComboBox, 1, 1);
    pGridLayoutBase->addWidget(pbtnDetial, 1, 2);

    connect(pbtnDetial, &QPushButton::clicked, this, &QtExtensionWidget::ShowDetial);

    m_pBaseWidget->setLayout(pGridLayoutBase);
}

void QtExtensionWidget::CreateExtenWidget()
{
    m_pExtenWidget = new QWidget;
    QGridLayout * pGridLayoutExten = new QGridLayout();

    QLabel * plbAge = new QLabel("Age:");
    QLineEdit * pLineEdit = new QLineEdit("30");

    pGridLayoutExten->addWidget(plbAge, 0, 0);
    pGridLayoutExten->addWidget(pLineEdit, 0, 1);

    QLabel * plbDeparment = new QLabel("Department:");
    QComboBox * pComboBox = new QComboBox();
    pComboBox->addItem("A");
    pComboBox->addItem("B");
    pComboBox->addItem("C");

    pGridLayoutExten->addWidget(plbDeparment, 1, 0);
    pGridLayoutExten->addWidget(pComboBox, 1, 1);

    m_pExtenWidget->setLayout(pGridLayoutExten);
}

void QtExtensionWidget::ShowDetial()
{
    if(m_pExtenWidget == nullptr)
        return;

    m_pExtenWidget->isHidden() ? m_pExtenWidget->show() : m_pExtenWidget->hide();

}
