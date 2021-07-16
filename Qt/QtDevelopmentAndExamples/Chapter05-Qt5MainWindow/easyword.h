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
#include <QLabel>

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


    QMenu * m_pMenuFile ;
    QAction * m_pNewAction ;
    QAction * m_pOpenAction ;
    QAction * m_pSaveAction ;
    QAction * m_pSaveAsAction ;
    QAction * m_pPrintAction ;

    QMenu * m_pMenuEdit;
    QAction * m_pRedoAction ;
    QAction * m_pCutAction ;
    QAction * m_pCopyAction ;
    QAction * m_pPasteAction ;

    QAction * m_pZoomInAction ;
    QAction * m_pZoomOutAction ;
    QAction * m_pRotate90Action ;
    QAction * m_pRotate180Action ;
    QAction * m_pRotate270Action ;

    QAction * m_pInsertTimeAction ;
    QAction * m_pInsertTextAction ;
    QAction * m_pInsertImageAction ;


    QMenu * m_pHelpMenu;
    QAction * m_pAbouNotepadAction ;
    QAction * m_pAboutQtAction ;


    QFontComboBox * m_pComboBoxFontType;
    QComboBox * m_pComboxFontSize;

    QToolButton * m_pBoldToolButton ;
    QToolButton * m_pItalicToolButton ;
    QToolButton * m_pUnderlineToolButton ;
    QToolButton * m_pColorToolButton ;
    QLabel * m_pLabelFontColor;

    QToolButton * m_pAlignLeftToolButton ;
    QToolButton * m_pAlignRightToolButton ;
    QToolButton * m_pAlignCenterToolButton ;
    QToolButton * m_pAlignJustifyToolButton ;



public slots:
    // ÎÄ¼þ action
    void New();
    void Open();
    void Save();
    void Exit();
    void Print();
    void SaveAs();

    // ±à¼­ action
    void ZoomIn();
    void ZoomOut();
    void Rotate90();
    void Rotate180();
    void Rotate270();

    void Bold();
    void Color();
    void Italic();
    void Underline();

    void AlignLeft();
    void AlignRight();
    void AlignCenter();
    void AlignJustify();
    void ShowCurrentFormatChanged(const QTextCharFormat &fmt);

    // °ïÖú
    void AboutQt();
    void AboutNotepad();    

    // ²åÈë
    void InsertTime();
    void InsertFile();
    void InsertImage();

private:
    void CreateAction();
    void CreateMenuWidget();
    void AddTextEditContextMenu();
    void InitMenuBar();
    void InitToolBar();

    void Binding();

};

#endif // EASYWORD_H
