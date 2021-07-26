#ifndef HISTOGRAMFORM_H
#define HISTOGRAMFORM_H

#include <QMainWindow>

#include <QStandardItemModel>
#include <QTableView>

namespace Ui {
class HistogramForm;
}

class HistogramForm : public QMainWindow
{
    Q_OBJECT

public:
    explicit HistogramForm(QWidget *parent = nullptr);
    ~HistogramForm();

private slots:
    void Open();

private:
    Ui::HistogramForm *ui;

    //
    void SetupModelHeaderData();
    void SetupView();

    QStandardItemModel * m_pStandardItemModel;
    QTableView * m_pTableView;
};

#endif // HISTOGRAMFORM_H
