#include "dirmodeex.h"
#include "ui_dirmodeex.h"


#include <QItemSelectionModel>
#include <QAbstractItemView>

#include <QHBoxLayout>
#include <QSplitter>


DirModeEx::DirModeEx(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::DirModeEx)
{
    ui->setupUi(this);

    m_pFileSystemModel = new QFileSystemModel;
    m_pFileSystemModel->setRootPath(QDir::currentPath());

    m_pFolderTreeView = new QTreeView;
    m_pFileListView = new QListView;
    m_pFileInfoTableView = new QTableView;

    m_pFolderTreeView->setModel(m_pFileSystemModel);
    m_pFileListView->setModel(m_pFileSystemModel);
    m_pFileInfoTableView->setModel(m_pFileSystemModel);

    m_pFolderTreeView->setSelectionMode(QAbstractItemView::SingleSelection);
    m_pFileListView->setSelectionMode(m_pFolderTreeView->selectionMode());
    m_pFileInfoTableView->setSelectionMode(QAbstractItemView::SingleSelection);

    connect(m_pFolderTreeView, &QTreeView::doubleClicked, m_pFileListView, &QListView::setRootIndex);
    connect(m_pFolderTreeView, &QTreeView::doubleClicked, m_pFileInfoTableView, &QTableView::setRootIndex);

    QSplitter * pSplitter = new QSplitter;

    pSplitter->addWidget(m_pFolderTreeView);
    pSplitter->addWidget(m_pFileListView);
    pSplitter->addWidget(m_pFileInfoTableView);

    this->setCentralWidget(pSplitter);

}

DirModeEx::~DirModeEx()
{
    delete ui;
}
