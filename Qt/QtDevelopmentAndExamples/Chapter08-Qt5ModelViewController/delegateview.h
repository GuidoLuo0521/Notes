#ifndef DELEGATEVIEW_H
#define DELEGATEVIEW_H

#include <QMainWindow>

// 模型
#include <QStandardItemModel>
// 视图
#include <QTableView>
// 视图中待插入控件
#include <QComboBox>    //
#include <QDateTimeEdit>
#include <QSpinBox>


namespace Ui {
class DelegateView;
}

class DelegateView : public QMainWindow
{
    Q_OBJECT

public:
    explicit DelegateView(QWidget *parent = nullptr);
    ~DelegateView();

private slots:
    void Open();
    void Save();

private:
    Ui::DelegateView *ui;

    QString m_strFilePath;

    QStandardItemModel * m_pStandardItemModel;
};

#endif // DELEGATEVIEW_H
