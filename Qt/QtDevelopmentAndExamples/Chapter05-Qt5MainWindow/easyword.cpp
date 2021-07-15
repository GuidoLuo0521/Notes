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
#include <QToolButton>

EasyWord::EasyWord(QMainWindow *parent) :
    QMainWindow(parent),
    ui(new Ui::EasyWord)
{
    ui->setupUi(this);

    setWindowTitle("Millet Word");

    CreateAction();
    CreateMenuWidget();
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
    QString strOpenPath = QFileDialog::getOpenFileName(this, "选择文件");
    if(strOpenPath == "")
        return;

    QFile file(strOpenPath);
    if( file.open( QIODevice::ReadWrite ) )
    {
        QString str = file.readAll();
        m_pTextEdit->setText(str);
    }
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

void EasyWord::Bold()
{
    m_pBoldToolButton->setChecked(!m_pBoldToolButton->isChecked());

    QTextCharFormat fmt;
    fmt.setFontWeight( m_pBoldToolButton->isChecked() ? QFont::Bold : QFont::Normal);
    m_pTextEdit->mergeCurrentCharFormat(fmt);

}

void EasyWord::Italic()
{

}

void EasyWord::Underline()
{

}

void EasyWord::Color()
{

}

void EasyWord::AlignLeft()
{

}

void EasyWord::AlignCenter()
{

}

void EasyWord::AlignRight()
{

}

void EasyWord::ShowCurrentFormatChanged(const QTextCharFormat &fmt)
{
    m_pComboBoxFontType->setCurrentIndex(m_pComboBoxFontType->findText(fmt.fontFamily()));
    m_pComboxFontSize->setCurrentIndex(m_pComboxFontSize->findText(QString::number(fmt.fontPointSize())));
    m_pBoldToolButton->setChecked(fmt.font().bold());
    m_pItalicToolButton->setChecked(fmt.fontItalic());
    m_pUnderlineToolButton->setChecked(fmt.fontUnderline());
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
    QString strPath = QFileDialog::getOpenFileName(this, "选择图片", "", strFilter);
    if(strPath == "")
        return;

    QTextCursor cursor = this->m_pTextEdit->textCursor();
    cursor.insertImage(strPath);
}

void EasyWord::InsertFile()
{
    QString strPath = QFileDialog::getOpenFileName(this, "选择文件");
    if(strPath == "")
        return;

    QFile file(strPath);
    if( file.open(QIODevice::ReadOnly) )
    {
        QTextCursor cursor = this->m_pTextEdit->textCursor();
        cursor.insertText(file.readAll());
    }
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
    m_pNewAction->setToolTip("新建");
    m_pNewAction->setShortcut(QKeySequence::New);
    m_pNewAction->setIcon(QIcon(":/Icons/icons/new.png"));

    m_pOpenAction = new QAction("打开(&O)");
    m_pOpenAction->setToolTip("打开");
    m_pOpenAction->setShortcut(QKeySequence::Open);
    m_pOpenAction->setIcon(QIcon(":/Icons/icons/open.png"));

    m_pSaveAction = new QAction("保存(&S)");
    m_pSaveAction->setToolTip("保存");
    m_pSaveAction->setShortcut(QKeySequence::Save);
    m_pSaveAction->setIcon(QIcon(":/Icons/icons/save.bmp"));

    m_pSaveAsAction = new QAction("另存为(&A)");
    m_pSaveAsAction->setToolTip("另存为");
    m_pSaveAsAction->setShortcut(QKeySequence::SaveAs);
    m_pSaveAsAction->setIcon(QIcon(":/Icons/icons/saveas.bmp"));

    m_pPrintAction = new QAction("打印(&P)");
    m_pPrintAction->setToolTip("打印");
    m_pPrintAction->setShortcut(QKeySequence::Print);
    m_pPrintAction->setIcon(QIcon(":/Icons/icons/printText.png"));

    // 编辑
    m_pRedoAction = new QAction("撤销(&U)");
    m_pRedoAction->setToolTip("撤销");
    m_pRedoAction->setShortcut(QKeySequence::Redo);
    m_pRedoAction->setIcon(QIcon(":/Icons/icons/redo.png"));

    m_pCutAction = new QAction("剪切(&T)");
    m_pCutAction->setToolTip("剪切");
    m_pCutAction->setShortcut(QKeySequence::Cut);
    m_pCutAction->setIcon(QIcon(":/Icons/icons/cut.png"));

    m_pCopyAction = new QAction("复制(&C)");
    m_pCopyAction->setToolTip("复制");
    m_pCopyAction->setShortcut(QKeySequence::Copy);
    m_pCopyAction->setIcon(QIcon(":/Icons/icons/copy.png"));

    m_pPasteAction = new QAction("粘贴(&P)");
    m_pPasteAction->setToolTip("粘贴");
    m_pPasteAction->setShortcut(QKeySequence::Paste);
    m_pPasteAction->setIcon(QIcon(":/Icons/icons/paste.png"));

    m_pDeleteAction = new QAction("删除(&L)");
    m_pDeleteAction->setToolTip("删除");
    m_pDeleteAction->setShortcut(QKeySequence::Delete);
    m_pDeleteAction->setIcon(QIcon(":/Icons/icons/delete.png"));

    m_pTimeAndDateAction = new QAction("时间/日期(&F5)");
    m_pTimeAndDateAction->setToolTip("插入时间");
    m_pTimeAndDateAction->setShortcut(QKeySequence("F5"));
    m_pTimeAndDateAction->setIcon(QIcon(":/Icons/icons/time.png"));

    m_pZoomInAction = new QAction("放大");
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
    m_pAbouNotepadAction->setToolTip("关于记事本");
    m_pAbouNotepadAction->setIcon(QIcon(":/Icons/icons/aboutnotepad.png"));

    m_pAboutQtAction = new QAction("关于Qt(&Q)");
    m_pAboutQtAction->setToolTip("关于Qt");
    m_pAboutQtAction->setIcon(QIcon(":/Icons/icons/aboutQt.png"));


    // toolbar
    m_pComboBoxFontType = new QFontComboBox;
    m_pComboBoxFontType->setFontFilters(QFontComboBox::ScalableFonts);

    m_pComboxFontSize = new QComboBox;
    QFontDatabase db;
    foreach(int size, db.standardSizes())
        m_pComboxFontSize->addItem(QString::number(size));
    m_pComboxFontSize->setCurrentText("20");

    m_pInsertImageAction = new QAction("插入图片");
    m_pInsertImageAction->setIcon(QIcon(":/Icons/icons/insertimage.png"));

    m_pInsertTextAction = new QAction("插入文件");
    m_pInsertTextAction->setIcon(QIcon(":/Icons/icons/text.png"));

}

void EasyWord::CreateMenuWidget()
{
    m_pBoldToolButton = new QToolButton;
    m_pBoldToolButton->setToolTip("加粗");
    m_pBoldToolButton->setChecked(false);
    m_pBoldToolButton->setShortcut(QKeySequence::Bold);
    m_pBoldToolButton->setIcon(QIcon(":/Icons/icons/bold.png"));

    m_pItalicToolButton = new QToolButton;
    m_pItalicToolButton->setToolTip("斜体");
    m_pItalicToolButton->setChecked(false);
    m_pItalicToolButton->setShortcut(QKeySequence::Italic);
    m_pItalicToolButton->setIcon(QIcon(":/Icons/icons/italic.png"));

    m_pUnderlineToolButton = new QToolButton;
    m_pUnderlineToolButton->setToolTip("下划线");
    m_pUnderlineToolButton->setChecked(false);
    m_pUnderlineToolButton->setShortcut(QKeySequence::Underline);
    m_pUnderlineToolButton->setIcon(QIcon(":/Icons/icons/underline.png"));

    m_pColorToolButton = new QToolButton;
    m_pColorToolButton->setToolTip("颜色");
    m_pColorToolButton->setChecked(false);
    m_pColorToolButton->setIcon(QIcon(":/Icons/icons/color.png"));

    m_pAlignLeftToolButton = new QToolButton;
    m_pUnderlineToolButton->setToolTip("左对齐");
    m_pAlignLeftToolButton->setIcon(QIcon(":/Icons/icons/left.png"));

    m_pAlignCenterToolButton = new QToolButton;
    m_pAlignCenterToolButton->setToolTip("居中");
    m_pAlignCenterToolButton->setIcon(QIcon(":/Icons/icons/center.png"));

    m_pAlignRightToolButton = new QToolButton;
    m_pAlignRightToolButton->setToolTip("右对齐");
    m_pAlignRightToolButton->setIcon(QIcon(":/Icons/icons/right.png"));
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
    pToolBarTextEdit->addAction(m_pInsertTextAction);
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
    pToolBarText->addWidget(m_pBoldToolButton);
    pToolBarText->addWidget(m_pItalicToolButton);
    pToolBarText->addWidget(m_pUnderlineToolButton);
    pToolBarText->addWidget(m_pColorToolButton);
    pToolBarText->addSeparator();
    pToolBarText->addWidget(m_pAlignLeftToolButton);
    pToolBarText->addWidget(m_pAlignCenterToolButton);
    pToolBarText->addWidget(m_pAlignRightToolButton);

    this->addToolBar(pToolBarText);

}

void EasyWord::AddTextEditContextMenu()
{
    m_pTextEdit->setContextMenuPolicy(Qt::CustomContextMenu);
    QMenu* stdMenu = new QMenu(m_pTextEdit);
    stdMenu->addAction(m_pInsertImageAction);
    stdMenu->addAction(m_pInsertTextAction);

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

    connect(m_pBoldToolButton, &QToolButton::clicked, this, &EasyWord::Bold);
    connect(m_pItalicToolButton, &QToolButton::clicked, this, &EasyWord::Italic);
    connect(m_pUnderlineToolButton, &QToolButton::clicked, this, &EasyWord::Underline);
    connect(m_pColorToolButton, &QToolButton::clicked, this, &EasyWord::Color);

    connect(m_pAlignLeftToolButton, &QToolButton::clicked, this, &EasyWord::AlignLeft);
    connect(m_pAlignCenterToolButton, &QToolButton::clicked, this, &EasyWord::AlignCenter);
    connect(m_pAlignRightToolButton, &QToolButton::clicked, this, &EasyWord::AlignRight);

    connect(m_pAbouNotepadAction, SIGNAL(triggered()), this, SLOT(AboutNotepad()));
    connect(m_pAboutQtAction, SIGNAL(triggered()), this, SLOT(AboutQt()));

    connect(m_pInsertTextAction, &QAction::triggered, this, &EasyWord::InsertFile);
    connect(m_pInsertImageAction, &QAction::triggered, this, &EasyWord::InsertImage);

    connect(m_pTextEdit, &QTextEdit::currentCharFormatChanged, this, &EasyWord::ShowCurrentFormatChanged);
}
