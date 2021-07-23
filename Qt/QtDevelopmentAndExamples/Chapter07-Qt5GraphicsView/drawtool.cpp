#include "drawtool.h"
#include <QDebug>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsView>
#include <QGraphicsLineItem>
#include <QtMath>

#define PI 3.1416

QList<DrawTool*> DrawTool::c_tools;
QPointF DrawTool::c_down;
QPointF DrawTool::c_last;
quint32 DrawTool::c_nDownFlags;

DrawShape DrawTool::c_drawShape = DS_Selection;

static SelectTool selectTool;
static RectTool   rectTool;
static RectTool   roundRectTool;
static RectTool   ellipseTool;

static LineTool lineTool;
static PolygonTool polygonTool(DS_Polygon);
static PolygonTool bezierTool(DS_Bezier);
static PolygonTool polylineTool(DS_Polyline);

static RotationTool rotationTool;

enum SelectMode
{
    none,
    netSelect,
    move,
    size,
    rotate,
    editor,
};

SelectMode selectMode = none;

static void setCursor(DrawScene * scene , const QCursor & cursor )
{
    QGraphicsView * view = scene->view();
    if (view)
        view->setCursor(cursor);
}

DrawTool::DrawTool(DrawShape shape)
{
    m_drawShape = shape ;
    m_hoverSizer = false;
    c_tools.push_back(this);
}

void DrawTool::mousePressEvent(QGraphicsSceneMouseEvent *event, DrawScene *scene)
{
    c_down = event->scenePos();
    c_last = event->scenePos();
}

void DrawTool::mouseMoveEvent(QGraphicsSceneMouseEvent *event, DrawScene *scene)
{
    c_last = event->scenePos();
    scene->update();
}

void DrawTool::mouseReleaseEvent(QGraphicsSceneMouseEvent *event, DrawScene *scene)
{
    if (event->scenePos() == c_down )
        c_drawShape = DS_Selection;

    setCursor(scene,Qt::ArrowCursor);

    scene->update();
}

void DrawTool::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event, DrawScene *scene)
{

}

DrawTool *DrawTool::findTool(DrawShape drawShape)
{
    QList<DrawTool*>::const_iterator iter = c_tools.constBegin();
    for ( ; iter != c_tools.constEnd() ; ++iter ){
        if ((*iter)->m_drawShape == drawShape )
            return (*iter);
    }
    return 0;
}

SelectTool::SelectTool()
    :DrawTool(DS_Selection)
{
    dashRect = 0;
    opposite_ = QPointF();
}

void SelectTool::mousePressEvent(QGraphicsSceneMouseEvent *event, DrawScene *scene)
{
    DrawTool::mousePressEvent(event,scene);

    setCursor(scene,Qt::ArrowCursor);

    c_down = event->scenePos();

    dashRect =  scene->itemAt(c_down, QTransform());

}

void SelectTool::mouseMoveEvent(QGraphicsSceneMouseEvent *event, DrawScene *scene)
{
    DrawTool::mouseMoveEvent(event, scene);

    c_last = event->scenePos();
    if(dashRect != nullptr)
    {
        dashRect->moveBy(c_last.x() - c_down.x(), c_last.y() - c_down.y());
        c_down = c_last;
    }

}

void SelectTool::mouseReleaseEvent(QGraphicsSceneMouseEvent *event, DrawScene *scene)
{
    DrawTool::mouseReleaseEvent(event,scene);

    c_down = event->scenePos();
    dashRect = nullptr;
}

RotationTool::RotationTool()
    :DrawTool(DS_Rotation)
{
    lastAngle = 0;
    dashRect = 0;
}

void RotationTool::mousePressEvent(QGraphicsSceneMouseEvent *event, DrawScene *scene)
{
    DrawTool::mousePressEvent(event,scene);
    if ( event->button() != Qt::LeftButton ) return;
}

void RotationTool::mouseMoveEvent(QGraphicsSceneMouseEvent *event, DrawScene *scene)
{
    DrawTool::mouseMoveEvent(event,scene);
}

void RotationTool::mouseReleaseEvent(QGraphicsSceneMouseEvent *event, DrawScene *scene)
{
    DrawTool::mouseReleaseEvent(event,scene);
    if ( event->button() != Qt::LeftButton ) return;
}

RectTool::RectTool() : DrawTool(DS_Rectangle)
{
    m_pItem = nullptr;
}

void RectTool::mousePressEvent(QGraphicsSceneMouseEvent *event, DrawScene *scene)
{

    if ( event->button() != Qt::LeftButton ) return;

    scene->clearSelection();

    c_down = event->scenePos();

    m_pItem = new QGraphicsRectItem;
    QPen pen(Qt::GlobalColor::black, 15);
    m_pItem->setPen(pen);
    m_pItem->setRect(c_down.x(), c_down.y(), 0, 0);
    scene->addItem(m_pItem);
    m_pItem->setSelected(true);

    //DrawTool::mousePressEvent(event,scene);

}

void RectTool::mouseMoveEvent(QGraphicsSceneMouseEvent *event, DrawScene *scene)
{
    setCursor(scene,Qt::CrossCursor);

    c_last = event->scenePos();
    if(m_pItem != nullptr)
        m_pItem->setRect(c_down.x(), c_down.y(), c_last.x() - c_down.x(), c_last.y() - c_down.y());

    scene->update();
}

void RectTool::mouseReleaseEvent(QGraphicsSceneMouseEvent *event, DrawScene *scene)
{
    selectTool.mouseReleaseEvent(event,scene);

    if( m_pItem )
    {
        m_pItem = nullptr;
    }
}


PolygonTool::PolygonTool(DrawShape shape)
    :DrawTool(shape)
{
    item = NULL;
    m_nPoints = 0;
}

void PolygonTool::mousePressEvent(QGraphicsSceneMouseEvent *event, DrawScene *scene)
{
    DrawTool::mousePressEvent(event,scene);

    if ( event->button() != Qt::LeftButton ) return;

}

void PolygonTool::mouseMoveEvent(QGraphicsSceneMouseEvent *event, DrawScene *scene)
{
    DrawTool::mouseMoveEvent(event,scene);
    setCursor(scene,Qt::CrossCursor);
}

void PolygonTool::mouseReleaseEvent(QGraphicsSceneMouseEvent *event, DrawScene *scene)
{
    DrawTool::mousePressEvent(event,scene);

}

void PolygonTool::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event, DrawScene *scene)
{
    DrawTool::mouseDoubleClickEvent(event,scene);
}

LineTool::LineTool() : DrawTool(DS_Line)
{

}

void LineTool::mousePressEvent(QGraphicsSceneMouseEvent *event, DrawScene *scene)
{
    if ( event->button() != Qt::LeftButton )
        return;

    scene->clearSelection();
    c_down = event->scenePos();

    m_pItem = new QGraphicsLineItem;
    QPen pen(Qt::GlobalColor::black, 15);
    m_pItem->setPen(pen);
    m_pItem->setLine(c_down.x(), c_down.y(), c_down.x(), c_down.y());
    scene->addItem(m_pItem);
    m_pItem->setSelected(true);

    scene->update();
}

void LineTool::mouseMoveEvent(QGraphicsSceneMouseEvent *event, DrawScene *scene)
{
    setCursor(scene,Qt::CrossCursor);

    if(m_pItem != nullptr)
        m_pItem->setLine(c_down.x(), c_down.y(), event->scenePos().x(), event->scenePos().y());

    scene->update();
}

void LineTool::mouseReleaseEvent(QGraphicsSceneMouseEvent *event, DrawScene *scene)
{
    if( m_pItem )
    {
        m_pItem = nullptr;
    }

    scene->clearSelection();

    selectTool.mouseReleaseEvent(event,scene);
}
