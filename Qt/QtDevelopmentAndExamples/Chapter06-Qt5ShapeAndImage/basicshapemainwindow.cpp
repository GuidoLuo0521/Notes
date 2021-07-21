#include "basicshapemainwindow.h"
#include "ui_basicshapemainwindow.h"


#include <QGridLayout>
#include <QLabel>
#include <QPen>
#include <QPushButton>
#include <QColorDialog>
#include <QLineEdit>
#include <QFontDialog>


BasicShapeMainWindow::BasicShapeMainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::BasicShapeMainWindow)
{
    ui->setupUi(this);

    CreateWidgets();
}

BasicShapeMainWindow::~BasicShapeMainWindow()
{
    delete ui;
}

void BasicShapeMainWindow::CreateWidgets()
{
    QWidget * pCentralWidget = this->centralWidget();

    // 左边 一个 PaintAreaWidget
    // 右边 属性选择
    QHBoxLayout * pMainLayout = new QHBoxLayout;

    // 左边
    m_pPaintAreaWidget = new PaintAreaWidget;
    m_pPaintAreaWidget->setAutoFillBackground(true);

    // 右边
    QGridLayout * pRightLayout = new QGridLayout;

    QLabel * pShape = new QLabel("形状：");
    m_pComboBoxShape = new QComboBox;
    m_pComboBoxShape->addItem("Line", PaintAreaWidget::Line);
    m_pComboBoxShape->addItem("Rectangle", PaintAreaWidget::Rectangle);
    m_pComboBoxShape->addItem("RoundRect", PaintAreaWidget::RoundRect);
    m_pComboBoxShape->addItem("Ellipse", PaintAreaWidget::Ellipse);
    m_pComboBoxShape->addItem("Polygon", PaintAreaWidget::Polygon);
    m_pComboBoxShape->addItem("Polyline", PaintAreaWidget::Polyline);
    m_pComboBoxShape->addItem("Points", PaintAreaWidget::Points);
    m_pComboBoxShape->addItem("Arc", PaintAreaWidget::Arc);
    m_pComboBoxShape->addItem("Path", PaintAreaWidget::Path);
    m_pComboBoxShape->addItem("Text", PaintAreaWidget::Text);
    m_pComboBoxShape->addItem("Pixmap", PaintAreaWidget::Pixmap);
    connect(m_pComboBoxShape, SIGNAL(currentIndexChanged(int)), m_pPaintAreaWidget, SLOT(ChangeShape(int)));

    QLabel * pPenColor = new QLabel("画笔颜色：");
    m_pFramePenColor = new QFrame;
    m_pFramePenColor->setAutoFillBackground(true);
    QPalette pltPen;
    pltPen.setColor(QPalette::Window, QColor(Qt::GlobalColor::black));
    m_pFramePenColor->setPalette(pltPen);
    QPushButton * pBtnChangePenColor = new QPushButton("更改");
    connect(pBtnChangePenColor, &QPushButton::clicked, this, &BasicShapeMainWindow::OnChangedPenColor);
    connect(this, SIGNAL(ChangePenColor(QColor)), m_pPaintAreaWidget, SLOT(ChangePenColor(QColor)));

    QLabel * pPenWidth = new QLabel("画笔宽度：");
    QSpinBox * m_pSpinBoxPenWidth = new QSpinBox;
    m_pSpinBoxPenWidth->setRange(1, 20);
    m_pSpinBoxPenWidth->setValue(1);
    //connect(m_pSpinBoxPenWidth, SIGNAL(valueChanged(int)), m_pPaintAreaWidget, SLOT(ChangePenWidth(int)));

    QObject::connect(m_pSpinBoxPenWidth, static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged), [=](int value)
                     {
                        m_pPaintAreaWidget->ChangePenWidth(value);
                     });


    QLabel * pPenStyle = new QLabel("画笔风格：");
    m_pComboBoxPenStyle = new QComboBox;
    m_pComboBoxPenStyle->addItem("NoPen", (int)Qt::NoPen);
    m_pComboBoxPenStyle->addItem("SolidLine", (int)Qt::SolidLine);
    m_pComboBoxPenStyle->addItem("DashLine", (int)Qt::DashLine);
    m_pComboBoxPenStyle->addItem("DotLine", (int)Qt::DotLine);
    m_pComboBoxPenStyle->addItem("DashDotLine", (int)Qt::DashDotLine);
    m_pComboBoxPenStyle->addItem("DashDotDotLine", (int)Qt::DashDotDotLine);
    m_pComboBoxPenStyle->addItem("CustomDashLine", (int)Qt::CustomDashLine);
    connect(m_pComboBoxPenStyle, SIGNAL(currentIndexChanged(int)), this, SLOT(OnChangedPenStyle(int)));
    connect(this, SIGNAL(ChangePenStyle(Qt::PenStyle)), m_pPaintAreaWidget, SLOT(ChangePenStyle(Qt::PenStyle)));

    QLabel * pPenEndCap = new QLabel("画笔顶帽：");
    m_pComboBoxPenCapStyle = new QComboBox;
    m_pComboBoxPenCapStyle->addItem("FlatCap", Qt::FlatCap);
    m_pComboBoxPenCapStyle->addItem("SquareCap", Qt::SquareCap);
    m_pComboBoxPenCapStyle->addItem("RoundCap", Qt::RoundCap);
    m_pComboBoxPenCapStyle->addItem("MPenCapStyle", Qt::MPenCapStyle);
    connect(m_pComboBoxPenCapStyle, SIGNAL(currentIndexChanged(int)), this, SLOT(OnChangedPenCapStyle(int)));
    connect(this, SIGNAL(ChangePenCapStyle(Qt::PenCapStyle)), m_pPaintAreaWidget, SLOT(ChangePenCapStyle(Qt::PenCapStyle)));

    QLabel * pPenJoin = new QLabel("连接点：");
    m_pComboBoxJoinStyle = new QComboBox;
    m_pComboBoxJoinStyle->addItem("MiterJoin", Qt::MiterJoin);
    m_pComboBoxJoinStyle->addItem("BevelJoin", Qt::BevelJoin);
    m_pComboBoxJoinStyle->addItem("RoundJoin", Qt::RoundJoin);
    m_pComboBoxJoinStyle->addItem("SvgMiterJoin", Qt::SvgMiterJoin);
    m_pComboBoxJoinStyle->addItem("MPenJoinStyle", Qt::MPenJoinStyle);
    connect(m_pComboBoxJoinStyle, SIGNAL(currentIndexChanged(int)), this, SLOT(OnChangedPenJoinStyle(int)));
    connect(this, SIGNAL(ChangePenJoinStyle(Qt::PenJoinStyle)), m_pPaintAreaWidget, SLOT(ChangePenJoinStyle(Qt::PenJoinStyle)));

    QLabel * pFillModel = new QLabel("填充模式：");
    m_pComboBoxFillRule = new QComboBox;
    m_pComboBoxFillRule->addItem("OddEvenFill", Qt::OddEvenFill);
    m_pComboBoxFillRule->addItem("WindingFill", Qt::WindingFill);
    connect(m_pComboBoxFillRule, SIGNAL(currentIndexChanged(int)), this, SLOT(OnChangedFillRule(int)));
    connect(this, SIGNAL(ChangeFillRule(Qt::FillRule)), m_pPaintAreaWidget, SLOT(ChangeFillRule(Qt::FillRule)));

    QLabel * pGradient = new QLabel("铺展效果：");
    m_pComboBoxSpread = new QComboBox;
    m_pComboBoxSpread->addItem("PadSpread", QGradient::PadSpread);
    m_pComboBoxSpread->addItem("RepeatSpread", QGradient::RepeatSpread);
    m_pComboBoxSpread->addItem("ReflectSpread", QGradient::ReflectSpread);
    connect(m_pComboBoxSpread, SIGNAL(currentIndexChanged(int)), this, SLOT(OnChangedSpread(int)));
    connect(this, SIGNAL(ChangeSpread(QGradient::Spread)), m_pPaintAreaWidget, SLOT(ChangeSpread(QGradient::Spread)));

    QLabel * pBrushColor = new QLabel("画笔颜色：");
    m_pFrameBrushColor = new QFrame;
    m_pFrameBrushColor->setAutoFillBackground(true);
    QPalette pltBrush;
    pltBrush.setColor(QPalette::Window, QColor(Qt::GlobalColor::black));
    m_pFrameBrushColor->setPalette(pltBrush);
    QPushButton * pBtnChangepltBrushColor = new QPushButton("更改");
    connect(pBtnChangepltBrushColor, &QPushButton::clicked, this, &BasicShapeMainWindow::OnChangedBrushColor);
    connect(this, SIGNAL(ChangeBrushColor(QColor)), m_pPaintAreaWidget, SLOT(ChangeBrushColor(QColor)));

    QLabel * pBrushStyle = new QLabel("画刷风格：");
    m_pComboBoxBrushStyle = new QComboBox;
    m_pComboBoxBrushStyle->addItem("NoBrush", (int)Qt::NoBrush);
    m_pComboBoxBrushStyle->addItem("SolidPattern", (int)Qt::SolidPattern);
    m_pComboBoxBrushStyle->addItem("Dense1Pattern", (int)Qt::Dense1Pattern);
    m_pComboBoxBrushStyle->addItem("Dense2Pattern", (int)Qt::Dense2Pattern);
    m_pComboBoxBrushStyle->addItem("Dense3Pattern", (int)Qt::Dense3Pattern);
    m_pComboBoxBrushStyle->addItem("Dense4Pattern", (int)Qt::Dense4Pattern);
    m_pComboBoxBrushStyle->addItem("Dense5Pattern", (int)Qt::Dense5Pattern);
    m_pComboBoxBrushStyle->addItem("Dense6Pattern", (int)Qt::Dense6Pattern);
    m_pComboBoxBrushStyle->addItem("Dense7Pattern", (int)Qt::Dense7Pattern);
    m_pComboBoxBrushStyle->addItem("HorPattern", (int)Qt::HorPattern);
    m_pComboBoxBrushStyle->addItem("VerPattern", (int)Qt::VerPattern);
    m_pComboBoxBrushStyle->addItem("CrossPattern", (int)Qt::CrossPattern);
    m_pComboBoxBrushStyle->addItem("BDiagPattern", (int)Qt::BDiagPattern);
    m_pComboBoxBrushStyle->addItem("FDiagPattern", (int)Qt::FDiagPattern);
    m_pComboBoxBrushStyle->addItem("DiagCrossPattern", (int)Qt::DiagCrossPattern);
    m_pComboBoxBrushStyle->addItem("LinearGradientPattern", (int)Qt::LinearGradientPattern);
    m_pComboBoxBrushStyle->addItem("RadialGradientPattern", (int)Qt::RadialGradientPattern);
    m_pComboBoxBrushStyle->addItem("ConicalGradientPattern", (int)Qt::ConicalGradientPattern);
    m_pComboBoxBrushStyle->addItem("TexturePattern", (int)Qt::TexturePattern);
    connect(m_pComboBoxBrushStyle, SIGNAL(currentIndexChanged(int)), this, SLOT(OnChangedBrushStyle(int)));
    connect(this, SIGNAL(ChangeBrushStyle(Qt::BrushStyle)), m_pPaintAreaWidget, SLOT(ChangeBrushStyle(Qt::BrushStyle)));

    QLabel * pDrawTextLabel = new QLabel("绘制内容：");
    QLineEdit * pLineEdit = new QLineEdit;
    connect(pLineEdit, &QLineEdit::textChanged, m_pPaintAreaWidget, &PaintAreaWidget::ChangeDrawText);

    QPushButton * pBtnFont = new QPushButton("字体");
    connect(pBtnFont, &QPushButton::clicked, this, &BasicShapeMainWindow::OnChangedTextFont);

    QPushButton * pBtnClearScreen = new QPushButton("清屏");
    connect(pBtnClearScreen, &QPushButton::clicked, m_pPaintAreaWidget, &PaintAreaWidget::ClearScreen);
    connect(this, SIGNAL(ChangeTextFont(QFont)), m_pPaintAreaWidget, SLOT(ChangeTextFont(QFont)));

    int nRow = 0, nColumn = 0;
    pRightLayout->addWidget(pShape, nRow, nColumn++);
    pRightLayout->addWidget(m_pComboBoxShape, nRow, nColumn++);

    ++nRow; nColumn = 0;
    pRightLayout->addWidget(pPenColor, nRow, nColumn++);
    pRightLayout->addWidget(m_pFramePenColor, nRow, nColumn++);
    pRightLayout->addWidget(pBtnChangePenColor, nRow, nColumn++);

    ++nRow; nColumn = 0;
    pRightLayout->addWidget(pPenWidth, nRow, nColumn++);
    pRightLayout->addWidget(m_pSpinBoxPenWidth, nRow, nColumn++);

    ++nRow; nColumn = 0;
    pRightLayout->addWidget(pPenStyle, nRow, nColumn++);
    pRightLayout->addWidget(m_pComboBoxPenStyle, nRow, nColumn++);

    ++nRow; nColumn = 0;
    pRightLayout->addWidget(pPenEndCap, nRow, nColumn++);
    pRightLayout->addWidget(m_pComboBoxPenCapStyle, nRow, nColumn++);

    ++nRow; nColumn = 0;
    pRightLayout->addWidget(pPenJoin, nRow, nColumn++);
    pRightLayout->addWidget(m_pComboBoxJoinStyle, nRow, nColumn++);

    ++nRow; nColumn = 0;
    pRightLayout->addWidget(pFillModel, nRow, nColumn++);
    pRightLayout->addWidget(m_pComboBoxFillRule, nRow, nColumn++);

    ++nRow; nColumn = 0;
    pRightLayout->addWidget(pGradient, nRow, nColumn++);
    pRightLayout->addWidget(m_pComboBoxSpread, nRow, nColumn++);

    ++nRow; nColumn = 0;
    pRightLayout->addWidget(pBrushColor, nRow, nColumn++);
    pRightLayout->addWidget(m_pFrameBrushColor, nRow, nColumn++);
    pRightLayout->addWidget(pBtnChangepltBrushColor, nRow, nColumn++);

    ++nRow; nColumn = 0;
    pRightLayout->addWidget(pBrushStyle, nRow, nColumn++);
    pRightLayout->addWidget(m_pComboBoxBrushStyle, nRow, nColumn++);

    ++nRow; nColumn = 0;
    pRightLayout->addWidget(pDrawTextLabel, nRow, nColumn++);
    pRightLayout->addWidget(pLineEdit, nRow, nColumn++);
    pRightLayout->addWidget(pBtnFont, nRow, nColumn++);

    ++nRow; nColumn = 0;
    pRightLayout->addWidget(pBtnClearScreen, nRow, 2);

    pMainLayout->addWidget(m_pPaintAreaWidget);
    pMainLayout->addLayout(pRightLayout);
    pMainLayout->setStretchFactor(m_pPaintAreaWidget, 1);
    pMainLayout->setStretchFactor(pRightLayout, 0);

    pCentralWidget->setLayout(pMainLayout);

}

void BasicShapeMainWindow::OnChangedPenColor()
{
    QColor color = QColorDialog::getColor();
    if( color.isValid() )
    {
        QPalette plt;
        plt.setColor(QPalette::Window, color);
        m_pFramePenColor->setPalette(plt);

        emit ChangePenColor(color);
    }
}

void BasicShapeMainWindow::OnChangedPenStyle(int style)
{
    emit ChangePenStyle((Qt::PenStyle)style);
}

void BasicShapeMainWindow::OnChangedPenCapStyle(int style)
{
/*
    enum PenCapStyle { // line endcap style
        FlatCap = 0x00,
        SquareCap = 0x10,
        RoundCap = 0x20,
        MPenCapStyle = 0x30
    };
*/
    Qt::PenCapStyle penstyle = Qt::FlatCap;
    switch (style) {
    case 0: penstyle = Qt::FlatCap; break;
    case 1: penstyle = Qt::SquareCap; break;
    case 2: penstyle = Qt::RoundCap; break;
    case 3: penstyle = Qt::MPenCapStyle; break;
    }

    // 1 << (style+16)
    emit ChangePenCapStyle(penstyle);
}

void BasicShapeMainWindow::OnChangedPenJoinStyle(int style)
{
/*
    enum PenJoinStyle { // line join style
        MiterJoin = 0x00,
        BevelJoin = 0x40,
        RoundJoin = 0x80,
        SvgMiterJoin = 0x100,
        MPenJoinStyle = 0x1c0
    };
*/

    Qt::PenJoinStyle joinstyle = Qt::PenJoinStyle::BevelJoin;
    switch (style) {
    case 0: joinstyle = Qt::MiterJoin; break;
    case 1: joinstyle = Qt::BevelJoin; break;
    case 2: joinstyle = Qt::RoundJoin; break;
    case 3: joinstyle = Qt::SvgMiterJoin; break;
    case 4: joinstyle = Qt::MPenJoinStyle; break;
    }
    emit ChangePenJoinStyle(joinstyle);
}

void BasicShapeMainWindow::OnChangedFillRule(int rule)
{
    emit ChangeFillRule((Qt::FillRule)rule);
}

void BasicShapeMainWindow::OnChangedSpread(int spread)
{
    emit ChangeSpread((QGradient::Spread)spread);
}

void BasicShapeMainWindow::OnChangedBrushColor()
{
    QColor color = QColorDialog::getColor();
    if( color.isValid() )
    {
        QPalette plt;
        plt.setColor(QPalette::Window, color);
        m_pFrameBrushColor->setPalette(plt);

        emit ChangeBrushColor(color);
    }
}

void BasicShapeMainWindow::OnChangedBrushStyle(int style)
{
    emit ChangeBrushStyle((Qt::BrushStyle)style);
}

void BasicShapeMainWindow::OnChangedTextFont()
{
    bool ok = true;
    QFont font = QFontDialog::getFont(&ok);

    emit ChangeTextFont(font);
}

