/**************************************************************************
**
** Copyright (C) 2019 sss0921.
** Contact: sss09217313@163.com
**
** This file is part of Drawing.
**
**************************************************************************/

#pragma once

#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>

class GraphicsImageItem;
class GraphicsImageScene : public QGraphicsScene
{
public:
    enum Mode { NormalMode, DrawShapePathMode };

    GraphicsImageScene(QObject *parent = nullptr);
    ~GraphicsImageScene();

    void clear();

    Mode mode() const;
    void setMode(Mode mode);

    QImage image() const;
    void setImage(const QImage &image);

protected:
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);

private:
    Mode m_mode;
    bool m_isDrawing;
    GraphicsImageItem *m_graphicsImageItem;
};
