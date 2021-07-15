#ifndef QTPALETTE_H
#define QTPALETTE_H

#include <QWidget>
#include <QComboBox>

namespace Ui {
class qtPalette;
}

class QtPalette : public QWidget
{
    Q_OBJECT

public:
    explicit QtPalette(QWidget *parent = nullptr);
    ~QtPalette();

private slots:
    void on_cbButton_currentIndexChanged(int index);

    void on_cbWindow_currentIndexChanged(int index);

    void on_cbWindowText_currentIndexChanged(int index);

    void on_cbButtonText_currentIndexChanged(int index);

    void on_cbBase_currentIndexChanged(int index);

private:
    Ui::qtPalette *ui;


private:
    void FillColorList(QComboBox * pCombobox);

    QColor GetColor(QComboBox *pCombobox);
    void SetPalette(QPalette::ColorRole role, QComboBox *pCombobox);
};

#endif // QTPALETTE_H
