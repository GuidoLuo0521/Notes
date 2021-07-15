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

    // �ļ�
    QMenu * m_pMenuFile ;
    QAction * m_pNewAction ;
    QAction * m_pOpenAction ;
    QAction * m_pSaveAction ;
    QAction * m_pSaveAsAction ;
    QAction * m_pPrintAction ;

    // �༭
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

    //����
    QMenu * m_pHelpMenu;
    QAction * m_pAbouNotepadAction ;
    QAction * m_pAboutQtAction ;

    // toolbar
    QFontComboBox * m_pComboBoxFontType;
    QComboBox * m_pComboxFontSize;

    QAction * m_pBoldAction ;
    QAction * m_pItalicAction ;
    QAction * m_pUnderlineAction ;
    QAction * m_pColorAction ;

    QAction * m_pAlignLeftAction ;
    QAction * m_pAlignRightAction ;
    QAction * m_pAlignCenterAction ;

    QAction * m_pInsertImageAction ;

private slots:
    // �ļ� action
    void New();
    void Open();
    void Save();
    void SaveAs();
    void PageSet();
    void Print();
    void Exit();

    // �༭ action
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

    // ����
    void AboutNotepad();
    void AboutQt();

    // ͼ��
    void InsertImage();


private:
    void CreateAction();
    void InitMenuBar();
    void InitToolBar();
    void AddTextEditContextMenu();
    void Binding();

};

#endif // EASYWORD_H
