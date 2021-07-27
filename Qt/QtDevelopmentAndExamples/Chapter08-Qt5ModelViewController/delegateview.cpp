#include "comboxdelegate.h"
#include "delegateview.h"
#include "datedelegate.h"
#include "ui_delegateview.h"

#include <QFileDialog>
#include <QMenu>
#include <QTextStream>

#include <datedelegate.h>



DelegateView::DelegateView(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::DelegateView)
{
    ui->setupUi(this);

    m_pStandardItemModel = new QStandardItemModel( 4, 4, this);;
    m_pStandardItemModel->setHeaderData(0, Qt::Horizontal, "姓名");
    m_pStandardItemModel->setHeaderData(1, Qt::Horizontal, "生日");
    m_pStandardItemModel->setHeaderData(2, Qt::Horizontal, "职业");
    m_pStandardItemModel->setHeaderData(3, Qt::Horizontal, "收入");

    QTableView * pTableView = new QTableView;

    DateDelegate *pDteDelegate = new DateDelegate(this);
    pTableView->setItemDelegateForColumn(1, pDteDelegate);
    ComboxDelegate * pComboxDelegate = new ComboxDelegate(this);
    pTableView->setItemDelegateForColumn(2, pComboxDelegate);


    pTableView->setModel(m_pStandardItemModel);
    pTableView->setSelectionMode(QAbstractItemView::SingleSelection);

    QMenu * pFileMenu = new QMenu("文件", this);
    QAction * pOpenFileAction = new QAction("打开");
    pFileMenu->addAction(pOpenFileAction);
    connect(pOpenFileAction, &QAction::triggered, this, &DelegateView::Open);

    QAction * pSaveFileAction = new QAction("保存");
    pFileMenu->addAction(pSaveFileAction);
    connect(pSaveFileAction, &QAction::triggered, this, &DelegateView::Save);

    this->menuBar()->addMenu(pFileMenu);

    QItemSelectionModel * pSelectionModel = new QItemSelectionModel(m_pStandardItemModel);
    pTableView->setSelectionModel(pSelectionModel);

    connect(pSelectionModel, SIGNAL(selectionChanged(QItemSelection, QItemSelection)), pTableView, SLOT(selectionChanged(QItemSelection, QItemSelection)));

    this->setCentralWidget(pTableView);
}

DelegateView::~DelegateView()
{
    delete ui;
}

void DelegateView::Open()
{
    QString strOpenPath = QFileDialog::getOpenFileName(this, "选择文件");
    if(strOpenPath == "")
        return;

    QFile file(strOpenPath);
    if( file.open( QIODevice::ReadOnly ) )
    {
        m_strFilePath = strOpenPath;
        QTextStream stream(&file);
        QString line = stream.readLine();
        int nRow = 0;

        m_pStandardItemModel->removeRows(0, m_pStandardItemModel->rowCount(QModelIndex()), QModelIndex());

        while (  !line.isEmpty() )
        {
            m_pStandardItemModel->insertRows(nRow, 1, QModelIndex());
            QStringList strList = line.split(",");
            m_pStandardItemModel->setData(m_pStandardItemModel->index( nRow, 0, QModelIndex()), strList.value(0));
            m_pStandardItemModel->setData(m_pStandardItemModel->index( nRow, 1, QModelIndex()), strList.value(1));
            m_pStandardItemModel->setData(m_pStandardItemModel->index( nRow, 2, QModelIndex()), strList.value(2));
            m_pStandardItemModel->setData(m_pStandardItemModel->index( nRow, 3, QModelIndex()), strList.value(3));

            nRow++;
            line = stream.readLine();
        }

        file.close();
    }
}

void DelegateView::Save()
{
    //QString strOpenPath = QFileDialog::getSaveFileName(this, "保存文件");
    if(m_strFilePath == "")
        return;

    QFile file(m_strFilePath);
    if( file.open( QIODevice::WriteOnly ) )
    {
        QString textData;
        int rows = m_pStandardItemModel->rowCount();
        int columns = m_pStandardItemModel->columnCount();

        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < columns; j++) {

                textData += m_pStandardItemModel->data(m_pStandardItemModel->index(i,j)).toString();
                textData += ",";  // for .csv file format
            }
            textData += "\r\n";    // (optional: for new line segmentation)
        }


        file.write(textData.toLocal8Bit().data());
        file.close();
    }
}

