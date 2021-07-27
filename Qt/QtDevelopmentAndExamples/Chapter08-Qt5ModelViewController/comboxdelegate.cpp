#include "comboxdelegate.h"

ComboxDelegate::ComboxDelegate(QObject * parent)
{

}

QWidget *ComboxDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    QComboBox * pEditor = new QComboBox(parent);
    pEditor->addItem("工人");
    pEditor->addItem("农民");
    pEditor->addItem("医生");
    pEditor->addItem("军人");
    pEditor->addItem("学生");

    // 安装事件过滤器，使得 ComboxDelegate 能够捕获 QComboBox 的事件
    pEditor->installEventFilter(const_cast<ComboxDelegate*>(this));

    return pEditor;
}

void ComboxDelegate::setEditorData(QWidget *pEditor, const QModelIndex &index) const
{
    // 获取指定箱的数据，并转为 string
    QString strDate = index.model()->data(index).toString();
    QComboBox *pBox = static_cast<QComboBox*>(pEditor);
    pBox->setCurrentIndex(pBox->findText(strDate));
}

void ComboxDelegate::setModelData(QWidget *pEditor, QAbstractItemModel *pModel, const QModelIndex &index) const
{
    QComboBox *pBox = static_cast<QComboBox*>(pEditor);
    pModel->setData(index, pBox->currentText());
}

void ComboxDelegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    editor->setGeometry(option.rect);
}
