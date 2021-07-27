#ifndef COMBOXDELEGATE_H
#define COMBOXDELEGATE_H

#include <QObject>
#include <QItemDelegate>
#include <QComboBox>
#include <QStyledItemDelegate>

class ComboxDelegate : public QStyledItemDelegate
{
    Q_OBJECT

public:
    ComboxDelegate(QObject * parent = 0);


    // 完成创建控件的工作
    // QModelIndex 指定的表项数据的编辑控件，并对控件的内容进行限定
    QWidget * createEditor(
        QWidget *parent,
        const QStyleOptionViewItem &option,
        const QModelIndex &index) const override;

    // 设置控件显示的数据，将 Model 中的数据更新至 Delegate 中，相当于一个初始化工作
    void setEditorData(
        QWidget * pEditor,
        const QModelIndex &index ) const override;

    // 将 Delegate中对数据的改变更新至Model中
    void setModelData(
        QWidget * pEditor,
        QAbstractItemModel * pModel,
        const QModelIndex &index ) const override;

    // 更新控件区域的显示
    void updateEditorGeometry(
        QWidget *editor,
        const QStyleOptionViewItem &option,
        const QModelIndex &index) const override;

};

#endif // DATEDELEGATE_H
