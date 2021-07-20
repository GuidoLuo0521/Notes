#include "easyword.h"
#include "ui_easyword.h"


#include <QMessageBox>
#include <QMdiArea>
#include <QMessageBox>
#include <QTextDocumentFragment>

#include <QColorDialog>
#include <QComboBox>
#include <QFileDialog>
#include <QFontComboBox>
#include <QFontDatabase>
#include <QGraphicsRectItem>
#include <QGridLayout>
#include <QLabel>
#include <QPrinter>
#include <QTextEdit>
#include <QTextStream>
#include <QTime>
#include <QToolButton>

#include <QPrintDialog>

EasyWord::EasyWord(QMainWindow *parent) :
    QMainWindow(parent),
    ui(new Ui::EasyWord)
{
    ui->setupUi(this);

    setWindowTitle("Millet Word");

    m_pTextEdit = new QTextEdit;
    setCentralWidget(m_pTextEdit);

    QTextCharFormat fmt;
    fmt.setFont(QFont("宋体", 20));
    MergeFormat(fmt);

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
    // 这里可以再判断是否修改过，没修改就不管这个
    if( m_pTextEdit->toPlainText() != "" )
    {
        if( QMessageBox::warning(this, "警告", "是否保存文件?", QMessageBox::Yes | QMessageBox::No) == QMessageBox::Yes)
        {
            if(m_strCurrentFilePath != "")
                Save();
            else
                SaveAs();
        }
    }

    m_strCurrentFilePath = "";
    m_pTextEdit->clear();
    this->setWindowTitle("Millet Word");
}
void EasyWord::Open()
{
    QString strOpenPath = QFileDialog::getOpenFileName(this, "选择文件");
    if(strOpenPath == "")
        return;

    QFile file(strOpenPath);
    if( file.open( QIODevice::ReadOnly ) )
    {
        QString str = file.readAll();
        m_pTextEdit->setText(str);

        m_strCurrentFilePath = strOpenPath;

        QFileInfo fileinfo(file);
        this->setWindowTitle("Millet Word  --  " + fileinfo.fileName());
    }
}
void EasyWord::Save()
{
    if(QFile::exists( m_strCurrentFilePath )== false)
        return;

    QFile file(m_strCurrentFilePath);
    if( file.open( QIODevice::WriteOnly ) )
    {
        QTextStream out(&file);
        out << m_pTextEdit->toHtml();
    }

    QMessageBox::information(this, "保存", "已保存");
}
void EasyWord::SaveAs()
{
    QString strSavePath = QFileDialog::getOpenFileName(this, "另存文件");
    if(strSavePath == "")
        return;

    QFile file(strSavePath);
    if( file.open( QIODevice::WriteOnly ) )
    {
        QTextStream out(&file);
        QString strHtml = m_pTextEdit->toHtml();
        out << strHtml;
    }

    QMessageBox::information(this, "另存", "已保存");
}

void EasyWord::Print()
{
    QPrinter printer;
    QPrintDialog printDialog(&printer, this);
    if (printDialog.exec() == QDialog::Accepted)
    {
        //----获取文本内容
        QTextDocument *doc = m_pTextEdit->document();
        // ---打开打印对话窗口
        doc->print(&printer);
    }

}
void EasyWord::Exit()
{

}

void EasyWord::InsertTime()
{
    QString strTime = QTime::currentTime().toString();
    //m_pTextEdit->append("strTime");

    QTextCursor cursor = m_pTextEdit->textCursor();
    cursor.insertText(strTime);
}

void EasyWord::ZoomIn()
{
    int nIndex = m_pComboxFontSize->currentIndex();
    if( (nIndex + 1) == m_pComboxFontSize->count())
        m_pComboxFontSize->setCurrentIndex(m_pComboxFontSize->count() - 1);
    else
        m_pComboxFontSize->setCurrentIndex(nIndex + 1 );

    double dFontSize = m_pComboxFontSize->currentText().toDouble();

    QTextCursor cursor = m_pTextEdit->textCursor();
    QTextImageFormat fmt = m_pTextEdit->currentCharFormat().toImageFormat();
    fmt.setWidth(fmt.width() + 5);
    fmt.setHeight(fmt.height() + 5);
    fmt.setFontPointSize(dFontSize);

    cursor.mergeCharFormat(fmt);
    //cursor.mergeCharFormat(fmt);
    //cursor.clearSelection();

    cursor.movePosition(QTextCursor::EndOfLine);//cursor和anchor均移至末尾
}

void EasyWord::ZoomOut()
{
    int nIndex = m_pComboxFontSize->currentIndex();
    if( nIndex == 0 )
        m_pComboxFontSize->setCurrentIndex(nIndex);
    else
        m_pComboxFontSize->setCurrentIndex(nIndex - 1 );

    double dFontSize = m_pComboxFontSize->currentText().toDouble();

    QTextCursor cursor = m_pTextEdit->textCursor();

    QTextImageFormat fmt = m_pTextEdit->currentCharFormat().toImageFormat();
    fmt.setWidth(fmt.width() - 5);
    fmt.setHeight(fmt.height() - 5);
    fmt.setFontPointSize(dFontSize);

    //fmt.setFont(QFont(fmt.fontFamily(), ));//参数依次是字体，大小，字体的粗细，以及是否斜体
    cursor.mergeCharFormat(fmt);
    //cursor.clearSelection();
    cursor.movePosition(QTextCursor::EndOfLine);//cursor和anchor均移至末尾
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
    QTextCharFormat fmt;
    fmt.setFontWeight( m_pBoldToolButton->isChecked() ? QFont::Bold : QFont::Normal);
    m_pTextEdit->mergeCurrentCharFormat(fmt);
    //m_pTextEdit->setFontWeight(m_pBoldToolButton->isChecked() ? QFont::Bold : QFont::Normal);

    /*
     * 调用QTextCursor的mergeCharFormat()函数把参数format所表示的格式应用到光标所在处的字符上
     * 调用QTextEdit的mergeCurrentCharFormat()函数把格式应用到选区内的所有字符上。
    */
}

void EasyWord::Italic()
{
    QTextCharFormat fmt;
    fmt.setFontItalic( m_pItalicToolButton->isChecked());
    m_pTextEdit->mergeCurrentCharFormat(fmt);
}

void EasyWord::Underline()
{
    QTextCharFormat fmt;
    fmt.setFontUnderline( m_pUnderlineToolButton->isChecked());
    m_pTextEdit->mergeCurrentCharFormat(fmt);
}

void EasyWord::Color()
{
    QColor color = QColorDialog::getColor( Qt::red, this);
    if(color.isValid())
    {
        QTextCharFormat fmt;
        fmt.setForeground(color);
        m_pTextEdit->mergeCurrentCharFormat(fmt);

        QPalette plt(color);
        m_pLabelFontColor->setPalette(plt);
    }
}

void EasyWord::AlignLeft()
{
    m_pTextEdit->setAlignment(Qt::AlignLeft);
}

void EasyWord::AlignCenter()
{
    m_pTextEdit->setAlignment(Qt::AlignCenter);
}

void EasyWord::AlignRight()
{
    m_pTextEdit->setAlignment(Qt::AlignRight);
}
void EasyWord::AlignJustify()
{
    m_pTextEdit->setAlignment(Qt::AlignJustify);
}

void EasyWord::ShowCurrentFormatChanged(const QTextCharFormat &fmt)
{
    m_pComboBoxFontType->setCurrentIndex(m_pComboBoxFontType->findText(fmt.fontFamily()));
    m_pComboxFontSize->setCurrentIndex(m_pComboxFontSize->findText(QString::number(fmt.fontPointSize())));
    m_pBoldToolButton->setChecked(fmt.font().bold());
    m_pItalicToolButton->setChecked(fmt.fontItalic());
    m_pUnderlineToolButton->setChecked(fmt.fontUnderline());

    QPalette plt(fmt.foreground().color());
    m_pLabelFontColor->setPalette(plt);
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
    QTextImageFormat fmt;

    QImage img(strPath);
    fmt.setWidth(img.width());
    fmt.setHeight(img.height());
    cursor.mergeCharFormat(fmt);
    cursor.insertImage(img);
}

void EasyWord::OnChangedFontComboBox(QString str)
{
    QTextCharFormat fmt;		 //创建一个QTextCharFormat对象
    fmt.setFontFamily(str); //选择的字体名称设置给QTextCharFormat对象
    MergeFormat(fmt);     		 //将新的格式应用到光标选区内的字符
}

void EasyWord::OnChangedSizeComboBox(QString str)
{
    QTextCharFormat fmt;
    fmt.setFontPointSize(str.toFloat());
    m_pTextEdit->mergeCurrentCharFormat(fmt);
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
    m_pUndoAction = new QAction("撤销(&U)");
    m_pUndoAction->setToolTip("撤销");
    m_pUndoAction->setShortcut(QKeySequence::Redo);
    m_pUndoAction->setIcon(QIcon(":/Icons/icons/redo.png"));

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

    m_pInsertTimeAction = new QAction("时间/日期(&F5)");
    m_pInsertTimeAction->setToolTip("插入时间");
    m_pInsertTimeAction->setShortcut(QKeySequence("F5"));
    m_pInsertTimeAction->setIcon(QIcon(":/Icons/icons/time.png"));

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

    m_pInsertImageAction = new QAction("插入图片");
    m_pInsertImageAction->setIcon(QIcon(":/Icons/icons/insertimage.png"));

    m_pInsertTextAction = new QAction("插入文件");
    m_pInsertTextAction->setIcon(QIcon(":/Icons/icons/text.png"));

    // 帮助
    m_pAbouNotepadAction = new QAction("关于记事本(&A)");
    m_pAbouNotepadAction->setToolTip("关于记事本");
    m_pAbouNotepadAction->setIcon(QIcon(":/Icons/icons/aboutnotepad.png"));

    m_pAboutQtAction = new QAction("关于Qt(&Q)");
    m_pAboutQtAction->setToolTip("关于Qt");
    m_pAboutQtAction->setIcon(QIcon(":/Icons/icons/aboutQt.png"));

}

void EasyWord::CreateMenuWidget()
{
    m_pComboBoxFontType = new QFontComboBox;
    m_pComboBoxFontType->setFontFilters(QFontComboBox::ScalableFonts);

    m_pComboxFontSize = new QComboBox;
    QFontDatabase db;
    foreach(int size, db.standardSizes())
        m_pComboxFontSize->addItem(QString::number(size));
    m_pComboxFontSize->setCurrentText("20");

    m_pBoldToolButton = new QToolButton;
    m_pBoldToolButton->setToolTip("加粗");
    m_pBoldToolButton->setCheckable(true);
    m_pBoldToolButton->setChecked(false);
    m_pBoldToolButton->setShortcut(QKeySequence::Bold);
    m_pBoldToolButton->setIcon(QIcon(":/Icons/icons/bold.png"));

    m_pItalicToolButton = new QToolButton;
    m_pItalicToolButton->setToolTip("斜体");
    m_pItalicToolButton->setCheckable(true);
    m_pItalicToolButton->setChecked(false);
    m_pItalicToolButton->setShortcut(QKeySequence::Italic);
    m_pItalicToolButton->setIcon(QIcon(":/Icons/icons/italic.png"));

    m_pUnderlineToolButton = new QToolButton;
    m_pUnderlineToolButton->setToolTip("下划线");
    m_pUnderlineToolButton->setCheckable(true);
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

    m_pAlignJustifyToolButton = new QToolButton;
    m_pAlignJustifyToolButton->setToolTip("两边对齐");
    m_pAlignJustifyToolButton->setIcon(QIcon(":/Icons/icons/justify.png"));
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
    m_pMenuEdit->addAction(m_pUndoAction);
    m_pMenuEdit->addSeparator();
    m_pMenuEdit->addAction(m_pCutAction);
    m_pMenuEdit->addAction(m_pCopyAction);
    m_pMenuEdit->addAction(m_pPasteAction);
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
    pToolBarTextEdit->addAction(m_pUndoAction);
    pToolBarTextEdit->addAction(m_pCutAction);
    pToolBarTextEdit->addAction(m_pCopyAction);
    pToolBarTextEdit->addAction(m_pPasteAction);
    pToolBarTextEdit->addSeparator();
    pToolBarTextEdit->addAction(m_pInsertTimeAction);
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
    m_pLabelFontColor = new QLabel;
    m_pLabelFontColor->resize(20, 20);
    m_pLabelFontColor->setFrameShape(QFrame::Box);

    // 当使用QPalette为窗口设定背景并使用QPalette::Window时
    // 必须调用setAutoFillBackground(true)!!!
    m_pLabelFontColor->setAutoFillBackground(true);
    m_pLabelFontColor->setPalette(QPalette(Qt::GlobalColor::black));

    pToolBarText->addWidget(pLabelFontType);
    pToolBarText->addWidget(m_pComboBoxFontType);
    pToolBarText->addSeparator();
    pToolBarText->addWidget(pLabelFontSize);
    pToolBarText->addWidget(m_pComboxFontSize);
    pToolBarText->addSeparator();
    pToolBarText->addWidget(m_pBoldToolButton);
    pToolBarText->addWidget(m_pItalicToolButton);
    pToolBarText->addWidget(m_pUnderlineToolButton);
    pToolBarText->addSeparator();
    pToolBarText->addWidget(m_pColorToolButton);
    pToolBarText->addWidget(m_pLabelFontColor);
    pToolBarText->addSeparator();
    pToolBarText->addWidget(m_pAlignLeftToolButton);
    pToolBarText->addWidget(m_pAlignCenterToolButton);
    pToolBarText->addWidget(m_pAlignRightToolButton);
    pToolBarText->addWidget(m_pAlignJustifyToolButton);

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
    //方式一
    //connect(m_pNewAction, SIGNAL(triggered()), this, SLOT(New()));
    //connect(m_pOpenAction, SIGNAL(triggered()), this, SLOT(Open()));
    //connect(m_pSaveAction, SIGNAL(triggered()), this, SLOT(Save()));
    //connect(m_pSaveAsAction, SIGNAL(triggered()), this, SLOT(SaveAs()));
    //connect(m_pPrintAction, SIGNAL(triggered()), this, SLOT(Print()));
    //
    //connect(m_pRedoAction, SIGNAL(triggered()), m_pTextEdit, SLOT(Redo()));
    //connect(m_pCutAction, SIGNAL(triggered()), m_pTextEdit, SLOT(Cut()));
    //connect(m_pCopyAction, SIGNAL(triggered()), m_pTextEdit, SLOT(Copy()));
    //connect(m_pPasteAction, SIGNAL(triggered()), m_pTextEdit, SLOT(Paste()));
    //connect(m_pDeleteAction, SIGNAL(triggered()), m_pTextEdit, SLOT(Delete()));
    //connect(m_pTimeAndDateAction, SIGNAL(triggered()), this, SLOT(TimeAndDate()));
    //connect(m_pZoomInAction, SIGNAL(triggered()), this, SLOT(ZoomIn()));
    //connect(m_pZoomOutAction, SIGNAL(triggered()), this, SLOT(ZoomOut()));
    //connect(m_pRotate90Action, SIGNAL(triggered()), this, SLOT(Rotate90()));
    //connect(m_pRotate180Action, SIGNAL(triggered()), this, SLOT(Rotate180()));
    //connect(m_pRotate270Action, SIGNAL(triggered()), this, SLOT(Rotate270()));


    connect(m_pNewAction, &QAction::triggered, this, &EasyWord::New);
    connect(m_pOpenAction, &QAction::triggered, this, &EasyWord::Open);
    connect(m_pSaveAction, &QAction::triggered, this, &EasyWord::Save);
    connect(m_pPrintAction, &QAction::triggered, this, &EasyWord::Print);
    connect(m_pSaveAsAction, &QAction::triggered, this, &EasyWord::SaveAs);

    connect(m_pCutAction, &QAction::triggered, m_pTextEdit, &QTextEdit::cut);
    connect(m_pCopyAction, &QAction::triggered, m_pTextEdit,&QTextEdit::copy);
    connect(m_pUndoAction, &QAction::triggered, m_pTextEdit, &QTextEdit::undo);
    connect(m_pPasteAction, &QAction::triggered, m_pTextEdit, &QTextEdit::paste);

    connect(m_pZoomInAction, &QAction::triggered, this, &EasyWord::ZoomIn);
    connect(m_pZoomOutAction, &QAction::triggered, this, &EasyWord::ZoomOut);
    connect(m_pRotate90Action, &QAction::triggered, this, &EasyWord::Rotate90);
    connect(m_pRotate180Action, &QAction::triggered, this, &EasyWord::Rotate180);
    connect(m_pRotate270Action, &QAction::triggered, this, &EasyWord::Rotate270);

    connect(m_pBoldToolButton, &QToolButton::clicked, this, &EasyWord::Bold);
    connect(m_pColorToolButton, &QToolButton::clicked, this, &EasyWord::Color);
    connect(m_pItalicToolButton, &QToolButton::clicked, this, &EasyWord::Italic);
    connect(m_pUnderlineToolButton, &QToolButton::clicked, this, &EasyWord::Underline);

    connect(m_pAlignLeftToolButton, &QToolButton::clicked, this, &EasyWord::AlignLeft);
    connect(m_pAlignRightToolButton, &QToolButton::clicked, this, &EasyWord::AlignRight);
    connect(m_pAlignCenterToolButton, &QToolButton::clicked, this, &EasyWord::AlignCenter);
    connect(m_pAlignJustifyToolButton, &QToolButton::clicked, this, &EasyWord::AlignJustify);

    connect(m_pAboutQtAction, &QAction::triggered, this, &EasyWord::AboutQt);
    connect(m_pAbouNotepadAction, &QAction::triggered, this, &EasyWord::AboutNotepad);

    connect(m_pInsertTextAction, &QAction::triggered, this, &EasyWord::InsertFile);
    connect(m_pInsertTimeAction, &QAction::triggered, this, &EasyWord::InsertTime);
    connect(m_pInsertImageAction, &QAction::triggered, this, &EasyWord::InsertImage);

    connect(m_pTextEdit, &QTextEdit::currentCharFormatChanged, this, &EasyWord::ShowCurrentFormatChanged);


    connect(m_pComboBoxFontType,SIGNAL(activated(QString)), this,SLOT(OnChangedFontComboBox(QString)));
    connect(m_pComboxFontSize,SIGNAL(activated(QString)),   this,SLOT(OnChangedSizeComboBox(QString)));

    // 方式一
    //connect(m_pNewAction, SIGNAL(triggered()), this, SLOT(New()));
    // 方式二
    //connect(m_pNewAction, &QAction::triggered, this, &EasyWord::New);
    // 有重载的时候
    //connect(m_pBtn, static_cast<void (MyButton::*)(bool)>(&MyButton::sigClicked), this, &Widget::onClicked);
    // 方式三
    //connect(m_pBtn, QOverload<bool>::of(&MyButton::sigClicked),this,&Widget::onClicked);
    // 第四种
    /*
    connect(m_pBtn, QOverload<bool>::of(&MyButton::sigClicked),
            [=](bool check){
                // do something

        });
     */

}

void EasyWord::MergeFormat(QTextCharFormat format)
{
    QTextCursor cursor =m_pTextEdit->textCursor();
    //获得编辑框中的光标
    if(!cursor.hasSelection())							//(a)
        cursor.select(QTextCursor::WordUnderCursor);
    cursor.mergeCharFormat(format);						//(b)
    m_pTextEdit->mergeCurrentCharFormat(format);	//(c)
}
