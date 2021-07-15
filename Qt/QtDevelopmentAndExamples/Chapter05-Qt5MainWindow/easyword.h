#ifndef EASYWORD_H
#define EASYWORD_H

#include <QMainWindow>

#include <QMenuBar>
#include <QAction>
#include <QKeySequence>
#include <QToolBar>
#include <QFileDialog>
#include <QFontComboBox>
#include <QTextEdit>
#include <QToolButton>

namespace Ui {
class EasyWord;
}

class EasyWord : public QMainWindow
{
    Q_OBJECT

public:
    explicit EasyWord(QMainWindow *parent = nullptr);
    ~EasyWord();

private:
    Ui::EasyWord *ui;

private:
    QTextEdit * m_pTextEdit;

    // ÎÄ¼þ
    QMenu * m_pMenuFile ;
    QAction * m_pNewAction ;
    QAction * m_pOpenAction ;
    QAction * m_pSaveAction ;
    QAction * m_pSaveAsAction ;
    QAction * m_pPrintAction ;

    // ±à¼­
    QMenu * m_pMenuEdit;
    QAction * m_pRedoAction ;
    QAction * m_pCutAction ;
    QAction * m_pCopyAction ;
    QAction * m_pPasteAction ;
    QAction * m_pDeleteAction ;
    QAction * m_pTimeAndDateAction ;

    QAction * m_pZoomInAction ;
    QAction * m_pZoomOutAction ;
    QAction * m_pRotate90Action ;
    QAction * m_pRotate180Action ;
    QAction * m_pRotate270Action ;

    //°ïÖú
    QMenu * m_pHelpMenu;
    QAction * m_pAbouNotepadAction ;
    QAction * m_pAboutQtAction ;

    // toolbar
    QFontComboBox * m_pComboBoxFontType;
    QComboBox * m_pComboxFontSize;

    QToolButton * m_pBoldToolButton ;
    QToolButton * m_pItalicToolButton ;
    QToolButton * m_pUnderlineToolButton ;
    QToolButton * m_pColorToolButton ;

    QToolButton * m_pAlignLeftToolButton ;
    QToolButton * m_pAlignRightToolButton ;
    QToolButton * m_pAlignCenterToolButton ;

    QAction * m_pInsertImageAction ;
    QAction * m_pInsertTextAction ;

public slots:
    // ÎÄ¼þ action
    void New();
    void Open();
    void Save();
    void SaveAs();
    void PageSet();
    void Print();
    void Exit();

    // ±à¼­ action
    void Redo();
    void Cut();
    void Copy();
    void Paste();
    void Delete();
    void TimeAndDate();
    void ZoomIn();
    void ZoomOut();
    void Rotate90();
    void Rotate180();
    void Rotate270();

    void Bold();
    void Italic();
    void Underline();
    void Color();

    void AlignLeft();
    void AlignCenter();
    void AlignRight();
    void ShowCurrentFormatChanged(const QTextCharFormat &fmt);

    // °ïÖú
    void AboutNotepad();
    void AboutQt();

    // Í¼Ïñ
    void InsertImage();
    void InsertFile();

private:
    void CreateAction();
    void CreateMenuWidget();
    void InitMenuBar();
    void InitToolBar();
    void AddTextEditContextMenu();
    void Binding();

};

#endif // EASYWORD_H
