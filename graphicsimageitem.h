/**************************************************************************
**
** Copyright (C) 2019 sss0921.
** Contact: sss09217313@163.com
**
** This file is part of Drawing.
**
**************************************************************************/

#pragma once

#include <QGraphicsItem>

class GraphicsImageItem : public QGraphicsItem
{
public:
    GraphicsImageItem(QGraphicsItem *parent = nullptr);

    QRectF boundingRect() const;

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
               QWidget *widget = nullptr);

    QImage image() const;
    void setImage(const QImage &image);

    QRectF rectf() const;
    void setRectf(const QRectF &rectf);

private:
    QRectF m_rectf;
    QImage m_image;
};
