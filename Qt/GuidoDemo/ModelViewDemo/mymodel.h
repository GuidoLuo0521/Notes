/*! @简要说明:
 *  @详细说明:
 *  @作者   : Guido
 *  @创建日期: 2022-01-26 15:21:05
 *  @版权   : Copyright By LIFOTRONIC, All Rights Reserved
 *
 **********************************************************
 *  @注意事项:
 *  @修改日志:
 *    1、https://doc.qt.io/qt-5/modelview.html#1-2-model-view-to-the-rescue
 *
 **********************************************************/


#ifndef MYMODEL_H
#define MYMODEL_H

#include <QAbstractTableModel>
#include <QTimer>

const int COLS= 3;
const int ROWS= 2;

class MyModel : public QAbstractTableModel
{
    Q_OBJECT

public:
    MyModel(QObject *parent = nullptr);

    // 重写函数
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const override;

    bool setData(const QModelIndex &index, const QVariant &value, int role) override;
    Qt::ItemFlags flags(const QModelIndex &index) const override;
signals:
    void editCompleted(const QString &);

private slots:
    void timerHit();

private:
    QTimer* timer;
    QString m_gridData[ROWS][COLS];  //holds text entered into QTableView

    // QAbstractItemModel interface
public:

};

#endif // MYMODEL_H
