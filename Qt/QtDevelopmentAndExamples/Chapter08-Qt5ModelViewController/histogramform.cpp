#include "histogramform.h"
#include "histogramview.h"
#include "ui_histogramform.h"

#include <QMenuBar>
#include <QMenu>
#include <QFileDialog>
#include <QTextStream>
#include <QSplitter>


HistogramForm::HistogramForm(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::HistogramForm)
{
    ui->setupUi(this);

    QMenu * pFileMenu = new QMenu("文件", this);
    QAction * pOpenFileAction = new QAction("打开");
    pFileMenu->addAction(pOpenFileAction);
    this->menuBar()->addMenu(pFileMenu);
    connect(pOpenFileAction, &QAction::triggered, this, &HistogramForm::Open);

    SetupModelHeaderData();
    SetupView();

}

HistogramForm::~HistogramForm()
{
    delete ui;
}

void HistogramForm::SetupModelHeaderData()
{
    m_pStandardItemModel = new QStandardItemModel( 4, 4, this);
    m_pStandardItemModel->setHeaderData(0, Qt::Horizontal, "部门");
    m_pStandardItemModel->setHeaderData(1, Qt::Horizontal, "男性");
    m_pStandardItemModel->setHeaderData(2, Qt::Horizontal, "女性");
    m_pStandardItemModel->setHeaderData(3, Qt::Horizontal, "退休");
}

void HistogramForm::SetupView()
{
    QSplitter * m_pSplitter = new QSplitter(Qt::Vertical);

    m_pTableView = new QTableView;
    m_pTableView->setModel(m_pStandardItemModel);
    m_pTableView->setSelectionMode(QAbstractItemView::SingleSelection);

    HistogramView * pHistogramView = new HistogramView;
    pHistogramView->setModel(m_pStandardItemModel);

    // 使用一个中间变量来同步两边
    QItemSelectionModel * pSelectionModel = new QItemSelectionModel(m_pStandardItemModel);
    m_pTableView->setSelectionModel(pSelectionModel);
    pHistogramView->setSelectionModel(pSelectionModel);



    //connect(pSelectionModel, &QItemSelectionModel::selectionChanged, m_pTableView, &QTableView::selectionChanged);
    // 以便于，自定义视图 HistogramView 对象中的选择变化能反映到 QTableView 对象的显示中。
    connect(pSelectionModel, SIGNAL(selectionChanged(QItemSelection, QItemSelection)), m_pTableView, SLOT(selectionChanged(QItemSelection, QItemSelection)));
    connect(pSelectionModel, SIGNAL(selectionChanged(QItemSelection, QItemSelection)), pHistogramView, SLOT(selectionChanged(QItemSelection, QItemSelection)));


    m_pSplitter->addWidget(m_pTableView);
    m_pSplitter->addWidget(pHistogramView);

    this->setCentralWidget(m_pSplitter);

}

void HistogramForm::Open()
{
    QString strOpenPath = QFileDialog::getOpenFileName(this, "选择文件");
    if(strOpenPath == "")
        return;

    QFile file(strOpenPath);
    if( file.open( QIODevice::ReadOnly ) )
    {
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
