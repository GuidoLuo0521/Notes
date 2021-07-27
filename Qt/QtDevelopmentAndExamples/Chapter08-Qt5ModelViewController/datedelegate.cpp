#include "datedelegate.h"


DateDelegate::DateDelegate(QObject *parent)
{

}

QWidget *DateDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    QDateTimeEdit * pEditor = new QDateTimeEdit(parent);
    pEditor->setDisplayFormat("yyyy-MM-dd");
    pEditor->setCalendarPopup(true);    // 设置日历选择的显示方式，下拉菜单

    // 安装事件过滤器，使得 DateDelegate 能够捕获 QDateTimeEdit 的事件
    pEditor->installEventFilter(const_cast<DateDelegate*>(this));

    return pEditor;
}

void DateDelegate::setEditorData(QWidget *pEditor, const QModelIndex &index) const
{
    // 获取指定箱的数据，并转为 string
    QString strDate = index.model()->data(index).toString();
    QDate date = QDate::fromString(strDate, Qt::ISODate);
    QDateTimeEdit *pEdit = static_cast<QDateTimeEdit*>(pEditor);
    pEdit->setDate(date);
}

void DateDelegate::setModelData(QWidget *pEditor, QAbstractItemModel *pModel, const QModelIndex &index) const
{
    QDateTimeEdit *pEdit = static_cast<QDateTimeEdit*>(pEditor);
    QDate date = pEdit->date();
    pModel->setData(index, QVariant(date.toString(Qt::ISODate)));
}

void DateDelegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    editor->setGeometry(option.rect);
}
