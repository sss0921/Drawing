/**************************************************************************
**
** Copyright (C) 2019 sss0921.
** Contact: sss09217313@163.com
**
** This file is part of Drawing.
**
**************************************************************************/

#include "graphicsimagescene.h"
#include "graphicsimageview.h"

GraphicsImageView::GraphicsImageView(QWidget *parent)
    : QGraphicsView(parent)
    , m_graphicsImageScene(new GraphicsImageScene(this))
{
    m_graphicsImageScene->setSceneRect(QRect(0, 0, 512, 512));
    setScene(m_graphicsImageScene);
}

QImage GraphicsImageView::image() const
{
    return m_graphicsImageScene->image();
}

void GraphicsImageView::setImage(const QImage &image)
{
    QRectF rectf = QRectF(QPointF(0, 0), image.size());
    scene()->setSceneRect(rectf);
    m_graphicsImageScene->setImage(image);

    fitInView(rectf, Qt::KeepAspectRatio);
}
