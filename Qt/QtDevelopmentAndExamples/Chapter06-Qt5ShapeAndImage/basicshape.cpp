#include "basicshape.h"
#include "ui_basicshape.h"

BasicShape::BasicShape(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::BasicShape)
{
    ui->setupUi(this);
}

BasicShape::~BasicShape()
{
    delete ui;
}
