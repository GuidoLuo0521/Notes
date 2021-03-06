#include "mymodel.h"

#include <QBrush>
#include <QFont>
#include <QDebug>
#include <QTime>


MyModel::MyModel(QObject *parent)
    : QAbstractTableModel(parent)
    , timer(new QTimer(this))
{
    timer->setInterval(1000);
    connect(timer, &QTimer::timeout , this, &MyModel::timerHit);
    timer->start();
}

int MyModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);

    return ROWS;
}

int MyModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);

    return COLS;
}

QVariant MyModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role == Qt::DisplayRole && orientation == Qt::Horizontal) {
        switch (section) {
        case 0:
            return QString("first");
        case 1:
            return QString("second");
        case 2:
            return QString("third");
        }
    }
    return QVariant();
}

bool MyModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (role == Qt::EditRole) {

        if (!checkIndex(index))
            return false;

        //save value from editor to member m_gridData
        m_gridData[index.row()][index.column()] = value.toString();

        //for presentation purposes only: build and emit a joined string
        QString result;
        for (int row = 0; row < ROWS; row++) {
            for (int col= 0; col < COLS; col++)
                result += m_gridData[row][col] + ' ';
        }

        emit editCompleted(result);
        return true;
    }
    return false;

}

Qt::ItemFlags MyModel::flags(const QModelIndex &index) const
{
    // 增加 ItemIsEditable flags
    return Qt::ItemIsEditable | QAbstractTableModel::flags(index);
}
#if false

QVariant MyModel::data(const QModelIndex &index, int role) const
{
    if (role == Qt::DisplayRole)
       return QString("Row%1, Column%2")
                   .arg(index.row() + 1)
                   .arg(index.column() +1);

    return QVariant();
}
#elif false

QVariant MyModel::data(const QModelIndex &index, int role) const
{
    static int count = 0;

    int row = index.row();
    int col = index.column();
    // generate a log message when this method gets called
    qDebug() << QString("row %1, col%2, role %3")
            .arg(row).arg(col).arg(role);

    switch (role) {
    case Qt::DisplayRole:
        qDebug() << QString("DisplayRole %1").arg(++count);
        if (row == 0 && col == 1) return QString("<--left");
        if (row == 1 && col == 1) return QString("right-->");

        return QString("Row%1, Column%2")
                .arg(row + 1)
                .arg(col +1);
    case Qt::FontRole:
        qDebug() << QString("FontRole %1").arg(++count);
        if (row == 0 && col == 0) { //change font only for cell(0,0)
            QFont boldFont;
            boldFont.setBold(true);
            return boldFont;
        }
        break;
    case Qt::BackgroundRole:
        qDebug() << QString("BackgroundRole %1").arg(++count);
        if (row == 1 && col == 2)  //change background only for cell(1,2)
            return QBrush(Qt::red);
        break;
    case Qt::TextAlignmentRole:
        qDebug() << QString("TextAlignmentRole %1").arg(++count);
        if (row == 1 && col == 1) //change text alignment only for cell(1,1)
            return int(Qt::AlignRight | Qt::AlignVCenter);
        break;
    case Qt::CheckStateRole:
        qDebug() << QString("CheckStateRole %1").arg(++count);
        if (row == 1 && col == 0) //add a checkbox to cell(1,0)
            return Qt::Checked;
        break;
    }
    qDebug() << QString("%1").arg(++count);
    return QVariant();
}
#elif true


QVariant MyModel::data(const QModelIndex &index, int role) const
{
    int row = index.row();
    int col = index.column();

    if (role == Qt::DisplayRole && row == 0 && col == 0)
        return QTime::currentTime().toString();

    return QVariant();
}

void MyModel::timerHit()
{
    //we identify the top left cell
    QModelIndex topLeft = createIndex(0,0);
    //emit a signal to make the view reread identified data
    emit dataChanged(topLeft, topLeft, {Qt::DisplayRole});
}

#endif
