#include "qtpalette.h"
#include "ui_qtpalette.h"

QtPalette::QtPalette(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::qtPalette)
{
    ui->setupUi(this);


    FillColorList(ui->cbBase);
    FillColorList(ui->cbWindow);
    FillColorList(ui->cbButton);
    FillColorList(ui->cbButtonText);
    FillColorList(ui->cbWindowText);

    ui->cbBase->setAutoFillBackground(true);
    ui->cbWindow->setAutoFillBackground(true);
    ui->cbButton->setAutoFillBackground(true);
    ui->cbButtonText->setAutoFillBackground(true);
    ui->cbWindowText->setAutoFillBackground(true);
    ui->btnFrameTest->setAutoFillBackground(true);
    ui->frame->setAutoFillBackground(true);

}

QtPalette::~QtPalette()
{
    delete ui;
}

void QtPalette::FillColorList(QComboBox * pCombobox)
{
    if( pCombobox == nullptr )
        return;

    QStringList colors = QColor::colorNames();
    QString color;

    pCombobox->clear();

    foreach( color, colors )
    {
        QPixmap pix(QSize(70, 20));
        pix.fill(QColor(color));

        pCombobox->addItem(QIcon(pix), NULL);
        pCombobox->setIconSize(QSize(70, 20));

        // ÉèÖÃÏÂÀ­³ß´ç
        pCombobox->setSizeAdjustPolicy(QComboBox::AdjustToContents);
    }
}

QColor QtPalette::GetColor( QComboBox * pCombobox )
{
    QStringList colors = QColor::colorNames();
    return QColor(colors[pCombobox->currentIndex()]);
}

void QtPalette::SetPalette(QPalette::ColorRole role, QComboBox * pCombobox)
{
    QPalette palette = ui->frame->palette();
    palette.setColor(role, GetColor(pCombobox));

    ui->frame->setPalette(palette);
    ui->frame->update();
}

void QtPalette::on_cbButton_currentIndexChanged(int index)
{
    SetPalette(QPalette::Button, ui->cbButton);
}

void QtPalette::on_cbWindow_currentIndexChanged(int index)
{
    SetPalette(QPalette::Window, ui->cbWindow);
}

void QtPalette::on_cbWindowText_currentIndexChanged(int index)
{
    SetPalette(QPalette::WindowText, ui->cbWindowText);
}

void QtPalette::on_cbButtonText_currentIndexChanged(int index)
{
    SetPalette(QPalette::ButtonText, ui->cbButtonText);
}

void QtPalette::on_cbBase_currentIndexChanged(int index)
{
    SetPalette(QPalette::Base, ui->cbBase);
}
