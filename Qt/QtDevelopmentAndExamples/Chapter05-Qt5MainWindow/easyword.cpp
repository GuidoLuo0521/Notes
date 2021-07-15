#include "easyword.h"
#include "ui_easyword.h"


#include <QMessageBox>
#include <QMdiArea>
#include <QMessageBox>
#include <QTextDocumentFragment>

#include <QComboBox>
#include <QFileDialog>
#include <QFontComboBox>
#include <QFontDatabase>
#include <QGridLayout>
#include <QLabel>
#include <QTextEdit>
#include <QTime>

EasyWord::EasyWord(QMainWindow *parent) :
    QMainWindow(parent),
    ui(new Ui::EasyWord)
{
    ui->setupUi(this);

    setWindowTitle("Millet Word");

    CreateAction();
    AddTextEditContextMenu();

    InitMenuBar();
    InitToolBar();

    Binding();

}

EasyWord::~EasyWord()
{
    delete ui;
}


/// slot
void EasyWord::New()
{

}
void EasyWord::Open()
{

}
void EasyWord::Save()
{

}
void EasyWord::SaveAs()
{

}
void EasyWord::PageSet()
{

}
void EasyWord::Print()
{

}
void EasyWord::Exit()
{

}

void EasyWord::Redo()
{

}
void EasyWord::Cut()
{
    QMessageBox::warning(this, "11", __FUNCTION__);
}
void EasyWord::Copy()
{

}
void EasyWord::Paste()
{

}
void EasyWord::Delete()
{

}

void EasyWord::TimeAndDate()
{
    QString strTime = QTime::currentTime().toString();
    //m_pTextEdit->append("strTime");

    QTextCursor cursor = m_pTextEdit->textCursor();
    cursor.insertText(strTime);
}

void EasyWord::ZoomIn()
{

}

void EasyWord::ZoomOut()
{

}

void EasyWord::Rotate90()
{

}

void EasyWord::Rotate180()
{

}

void EasyWord::Rotate270()
{

}

void EasyWord::AboutNotepad()
{

}

void EasyWord::AboutQt()
{
    QMessageBox::aboutQt(this);
}

void EasyWord::InsertImage()
{
    QString strFilter = "图片|*.jpg;*.png;*.bmp";
    QString strImagePath = QFileDialog::getOpenFileName(this, "选择图片", "", strFilter);
    if(strImagePath == "")
        return;

    QTextCursor cursor = this->m_pTextEdit->textCursor();
    cursor.insertImage(strImagePath);
}

void EasyWord::CreateAction()
{

    m_pTextEdit = new QTextEdit;
    setCentralWidget(m_pTextEdit);

    QTextDocumentFragment fragment;
    fragment = QTextDocumentFragment::fromHtml("<img width=80 height=50 "
                                               "src=':/Icons/icons/delete.png'>");
    m_pTextEdit->textCursor().insertFragment(fragment);
    m_pTextEdit->setFont(QFont("宋体", 20));

    // 文件
    m_pNewAction = new QAction("新建(&N)");
    m_pNewAction->setShortcut(QKeySequence::New);
    m_pNewAction->setIcon(QIcon(":/Icons/icons/new.png"));

    m_pOpenAction = new QAction("打开(&O)");
    m_pOpenAction->setShortcut(QKeySequence::Open);
    m_pOpenAction->setIcon(QIcon(":/Icons/icons/open.png"));

    m_pSaveAction = new QAction("保存(&S)");
    m_pSaveAction->setShortcut(QKeySequence::Save);
    m_pSaveAction->setIcon(QIcon(":/Icons/icons/save.bmp"));

    m_pSaveAsAction = new QAction("另存为(&A)");
    m_pSaveAsAction->setShortcut(QKeySequence::SaveAs);
    m_pSaveAsAction->setIcon(QIcon(":/Icons/icons/saveas.bmp"));

    m_pPrintAction = new QAction("打印(&P)");
    m_pPrintAction->setShortcut(QKeySequence::Print);
    m_pPrintAction->setIcon(QIcon(":/Icons/icons/printText.png"));

    // 编辑
    m_pRedoAction = new QAction("撤销(&U)");
    m_pRedoAction->setShortcut(QKeySequence::Redo);
    m_pRedoAction->setIcon(QIcon(":/Icons/icons/redo.png"));

    m_pCutAction = new QAction("剪切(&T)");
    m_pCutAction->setShortcut(QKeySequence::Cut);
    m_pCutAction->setIcon(QIcon(":/Icons/icons/cut.png"));

    m_pCopyAction = new QAction("复制(&C)");
    m_pCopyAction->setShortcut(QKeySequence::Copy);
    m_pCopyAction->setIcon(QIcon(":/Icons/icons/copy.png"));

    m_pPasteAction = new QAction("粘贴(&P)");
    m_pPasteAction->setShortcut(QKeySequence::Paste);
    m_pPasteAction->setIcon(QIcon(":/Icons/icons/paste.png"));

    m_pDeleteAction = new QAction("删除(&L)");
    m_pDeleteAction->setShortcut(QKeySequence::Delete);
    m_pDeleteAction->setIcon(QIcon(":/Icons/icons/delete.png"));

    m_pTimeAndDateAction = new QAction("时间/日期(&F5)");
    m_pTimeAndDateAction->setToolTip("插入时间");
    m_pTimeAndDateAction->setShortcut(QKeySequence("F5"));
    m_pTimeAndDateAction->setIcon(QIcon(":/Icons/icons/time.png"));

    m_pZoomInAction = new QAction("(放大)");
    m_pZoomInAction->setShortcut(QKeySequence("Ctrl+="));
    m_pZoomInAction->setIcon(QIcon(":/Icons/icons/zoomin.png"));

    m_pZoomOutAction = new QAction("缩小");
    m_pZoomOutAction->setShortcut(QKeySequence("Ctrl+-"));
    m_pZoomOutAction->setIcon(QIcon(":/Icons/icons/zoomout.png"));

    m_pRotate90Action = new QAction("旋转90°");
    m_pRotate90Action->setShortcut(QKeySequence("Ctrl+Right"));
    m_pRotate90Action->setIcon(QIcon(":/Icons/icons/rotate90.png"));

    m_pRotate180Action = new QAction("旋转180°");
    m_pRotate180Action->setShortcut(QKeySequence("Ctrl+Down"));
    m_pRotate180Action->setIcon(QIcon(":/Icons/icons/rotate180.png"));

    m_pRotate270Action = new QAction("旋转270°");
    m_pRotate270Action->setShortcut(QKeySequence("Ctrl+Left"));
    m_pRotate270Action->setIcon(QIcon(":/Icons/icons/rotate270.png"));

    // 帮助
    m_pAbouNotepadAction = new QAction("关于记事本(&A)");
    m_pAbouNotepadAction->setIcon(QIcon(":/Icons/icons/aboutnotepad.png"));

    m_pAboutQtAction = new QAction("关于Qt(&Q)");
    m_pAboutQtAction->setIcon(QIcon(":/Icons/icons/aboutQt.png"));


    // toolbar
    m_pComboBoxFontType = new QFontComboBox;
    m_pComboBoxFontType->setFontFilters(QFontComboBox::ScalableFonts);

    m_pComboxFontSize = new QComboBox;
    QFontDatabase db;
    foreach(int size, db.standardSizes())
        m_pComboxFontSize->addItem(QString::number(size));
    m_pComboxFontSize->setCurrentText("20");

    m_pBoldAction = new QAction("加粗");
    m_pBoldAction->setShortcut(QKeySequence::Bold);
    m_pBoldAction->setIcon(QIcon(":/Icons/icons/bold.png"));

    m_pItalicAction = new QAction("斜体");
    m_pItalicAction->setShortcut(QKeySequence::Italic);
    m_pItalicAction->setIcon(QIcon(":/Icons/icons/italic.png"));

    m_pUnderlineAction = new QAction("下划线");
    m_pUnderlineAction->setShortcut(QKeySequence::Underline);
    m_pUnderlineAction->setIcon(QIcon(":/Icons/icons/underline.png"));

    m_pColorAction = new QAction("颜色");
    m_pColorAction->setIcon(QIcon(":/Icons/icons/color.png"));

    m_pAlignLeftAction = new QAction("左对齐");
    m_pAlignLeftAction->setIcon(QIcon(":/Icons/icons/left.png"));

    m_pAlignCenterAction = new QAction("居中");
    m_pAlignCenterAction->setIcon(QIcon(":/Icons/icons/center.png"));

    m_pAlignRightAction = new QAction("右对齐");
    m_pAlignRightAction->setIcon(QIcon(":/Icons/icons/right.png"));

    m_pInsertImageAction = new QAction("插入图片");
    m_pInsertImageAction->setIcon(QIcon(":/Icons/icons/insertimage.png"));

}


void EasyWord::InitMenuBar()
{
    QMenuBar * pMenuBar = ui->menubar;

    // 文件
    m_pMenuFile = new QMenu("文件(&F)");
    m_pMenuFile->addAction(m_pNewAction);
    m_pMenuFile->addAction(m_pOpenAction);
    m_pMenuFile->addSeparator();
    m_pMenuFile->addAction(m_pSaveAction);
    m_pMenuFile->addAction(m_pSaveAsAction);
    m_pMenuFile->addSeparator();
    m_pMenuFile->addAction(m_pPrintAction);

    pMenuBar->addMenu(m_pMenuFile);

    // 编辑
    m_pMenuEdit = new QMenu("编辑(&F)");
    //
    m_pMenuEdit->addAction(m_pRedoAction);
    m_pMenuEdit->addSeparator();
    m_pMenuEdit->addAction(m_pCutAction);
    m_pMenuEdit->addAction(m_pCopyAction);
    m_pMenuEdit->addAction(m_pPasteAction);
    m_pMenuEdit->addAction(m_pDeleteAction);
    m_pMenuEdit->addAction(m_pTimeAndDateAction);
    m_pMenuEdit->addSeparator();
    m_pMenuEdit->addAction(m_pZoomInAction);
    m_pMenuEdit->addAction(m_pZoomOutAction);
    m_pMenuEdit->addAction(m_pRotate90Action);
    m_pMenuEdit->addAction(m_pRotate180Action);
    m_pMenuEdit->addAction(m_pRotate270Action);

    pMenuBar->addMenu(m_pMenuEdit);


    // 帮助
    QMenu * pMenu = new QMenu(tr("帮助(&H)"));
    pMenu->addAction(m_pAbouNotepadAction);
    pMenu->addAction(m_pAboutQtAction);

    pMenuBar->addMenu(pMenu);

}

void EasyWord::InitToolBar()
{
    QToolBar * pToolBarFile = new QToolBar("文件");
    pToolBarFile->addAction(m_pNewAction);
    pToolBarFile->addAction(m_pOpenAction);
    pToolBarFile->addAction(m_pSaveAction);
    pToolBarFile->addAction(m_pSaveAsAction);
    pToolBarFile->addAction(m_pPrintAction);
    this->addToolBar(pToolBarFile);

    QToolBar * pToolBarTextEdit = new QToolBar("文字编辑");
    pToolBarTextEdit->addAction(m_pRedoAction);
    pToolBarTextEdit->addAction(m_pCutAction);
    pToolBarTextEdit->addAction(m_pCopyAction);
    pToolBarTextEdit->addAction(m_pPasteAction);
    pToolBarTextEdit->addAction(m_pDeleteAction);
    pToolBarTextEdit->addSeparator();
    pToolBarTextEdit->addAction(m_pTimeAndDateAction);
    pToolBarTextEdit->addAction(m_pInsertImageAction);
    this->addToolBar(pToolBarTextEdit);

    QToolBar * pToolBarImage = new QToolBar("图像编辑");
    pToolBarImage->addAction(m_pZoomInAction);
    pToolBarImage->addAction(m_pZoomOutAction);
    pToolBarImage->addAction(m_pRotate90Action);
    pToolBarImage->addAction(m_pRotate180Action);
    pToolBarImage->addAction(m_pRotate270Action);
    this->addToolBar(pToolBarImage);

    QToolBar * pToolBarText = new QToolBar("文本编辑");
    QLabel * pLabelFontType = new QLabel("字体：");
    QLabel * pLabelFontSize = new QLabel("字号：");
    pToolBarText->addWidget(pLabelFontType);
    pToolBarText->addWidget(m_pComboBoxFontType);
    pToolBarText->addSeparator();
    pToolBarText->addWidget(pLabelFontSize);
    pToolBarText->addWidget(m_pComboxFontSize);
    pToolBarText->addSeparator();
    pToolBarText->addAction(m_pBoldAction);
    pToolBarText->addAction(m_pItalicAction);
    pToolBarText->addAction(m_pUnderlineAction);
    pToolBarText->addAction(m_pColorAction);
    pToolBarText->addSeparator();
    pToolBarText->addAction(m_pAlignLeftAction);
    pToolBarText->addAction(m_pAlignCenterAction);
    pToolBarText->addAction(m_pAlignRightAction);

    this->addToolBar(pToolBarText);

}

void EasyWord::AddTextEditContextMenu()
{
    m_pTextEdit->setContextMenuPolicy(Qt::CustomContextMenu);
    QMenu* stdMenu = new QMenu(m_pTextEdit);
    stdMenu->addAction(m_pInsertImageAction);

    QObject::connect(m_pTextEdit, &QTextEdit::customContextMenuRequested, [=](QPoint x)
                     {
                         stdMenu->move(m_pTextEdit->mapToGlobal(x));
                         stdMenu->show();
                     });
}

void EasyWord::Binding()
{
    connect(m_pNewAction, SIGNAL(triggered()), this, SLOT(New()));
    connect(m_pOpenAction, SIGNAL(triggered()), this, SLOT(Open()));
    connect(m_pSaveAction, SIGNAL(triggered()), this, SLOT(Save()));
    connect(m_pSaveAsAction, SIGNAL(triggered()), this, SLOT(SaveAs()));
    connect(m_pPrintAction, SIGNAL(triggered()), this, SLOT(Print()));

    connect(m_pRedoAction, SIGNAL(triggered()), this, SLOT(Redo()));
    connect(m_pCutAction, SIGNAL(triggered()), this, SLOT(Cut()));
    connect(m_pCopyAction, SIGNAL(triggered()), this, SLOT(Copy()));
    connect(m_pPasteAction, SIGNAL(triggered()), this, SLOT(Paste()));
    connect(m_pDeleteAction, SIGNAL(triggered()), this, SLOT(Delete()));
    connect(m_pTimeAndDateAction, SIGNAL(triggered()), this, SLOT(TimeAndDate()));
    connect(m_pZoomInAction, SIGNAL(triggered()), this, SLOT(ZoomIn()));
    connect(m_pZoomOutAction, SIGNAL(triggered()), this, SLOT(ZoomOut()));
    connect(m_pRotate90Action, SIGNAL(triggered()), this, SLOT(Rotate90()));
    connect(m_pRotate180Action, SIGNAL(triggered()), this, SLOT(Rotate180()));
    connect(m_pRotate270Action, SIGNAL(triggered()), this, SLOT(Rotate270()));

    connect(m_pAbouNotepadAction, SIGNAL(triggered()), this, SLOT(AboutNotepad()));
    connect(m_pAboutQtAction, SIGNAL(triggered()), this, SLOT(AboutQt()));

    connect(m_pInsertImageAction, &QAction::triggered, this, &EasyWord::InsertImage);
}
