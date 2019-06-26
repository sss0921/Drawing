/**************************************************************************
**
** Copyright (C) 2019 sss0921.
** Contact: sss09217313@163.com
**
** This file is part of Drawing.
**
**************************************************************************/

#include "graphicsimageitem.h"
#include "graphicsimagescene.h"

GraphicsImageScene::GraphicsImageScene(QObject *parent)
    : QGraphicsScene(parent)
    , m_mode(NormalMode)
    , m_isDrawing(false)
    , m_graphicsImageItem(new GraphicsImageItem)
{
    addItem(m_graphicsImageItem);
}

GraphicsImageScene::~GraphicsImageScene()
{
    clear();
}

void GraphicsImageScene::clear()
{
    removeItem(m_graphicsImageItem);

    if (m_graphicsImageItem)
        delete m_graphicsImageItem;
}

GraphicsImageScene::Mode GraphicsImageScene::mode() const
{
    return m_mode;
}

void GraphicsImageScene::setMode(Mode mode)
{
    if (m_mode != mode)
        m_mode = mode;
}

QImage GraphicsImageScene::image() const
{
    return m_graphicsImageItem->image();
}

void GraphicsImageScene::setImage(const QImage &image)
{
    QRectF rectf = QRectF(QPointF(0, 0), image.size());
    m_graphicsImageItem->setRectf(rectf);
    m_graphicsImageItem->setImage(image);
}

void GraphicsImageScene::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    if (m_isDrawing) {
        // add points to item
    }
    QGraphicsScene::mouseMoveEvent(event);
}

void GraphicsImageScene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if (m_mode == DrawShapePathMode) {
        if (event->button() & Qt::LeftButton) {
            m_isDrawing = true;
        } else if (event->button() & Qt::RightButton) {
            m_isDrawing = false;
        }
    }
    QGraphicsScene::mousePressEvent(event);
}

void GraphicsImageScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    if (m_mode == DrawShapePathMode) {
        m_isDrawing = false;
    }
    QGraphicsScene::mouseReleaseEvent(event);
}
