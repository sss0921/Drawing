#include "graphicsimageitem.h"

#include <QPainter>

GraphicsImageItem::GraphicsImageItem(QGraphicsItem *parent)
    : QGraphicsItem(parent)
{
}

QRectF GraphicsImageItem::boundingRect() const
{
    return m_rectf;
}

void GraphicsImageItem::paint(QPainter *painter, const QStyleOptionGraphicsItem * /*option*/,
                              QWidget * /*widget*/)
{
    painter->drawImage(m_rectf, m_image);
}

QImage GraphicsImageItem::image() const
{
    return m_image;
}

void GraphicsImageItem::setImage(const QImage &image)
{
    m_image = image;
    update(m_rectf);
}

QRectF GraphicsImageItem::rectf() const
{
    return m_rectf;
}

void GraphicsImageItem::setRectf(const QRectF &rectf)
{
    m_rectf = rectf;
    update(m_rectf);
}
