#ifndef DIRMODEEX_H
#define DIRMODEEX_H

#include <QMainWindow>

#include <QTreeView>    // 显示文件夹
#include <QListView>    // 显示文件列表
#include <QTableView>   // 显示文件信息
#include <QFileSystemModel>    // `QDirModel`：文件和目录的存储模型

namespace Ui {
class DirModeEx;
}

class DirModeEx : public QMainWindow
{
    Q_OBJECT

public:
    explicit DirModeEx(QWidget *parent = nullptr);
    ~DirModeEx();

private:
    Ui::DirModeEx *ui;


    QTreeView * m_pFolderTreeView;
    QListView * m_pFileListView;
    QTableView * m_pFileInfoTableView;

    QFileSystemModel *m_pFileSystemModel;


};

#endif // DIRMODEEX_H
