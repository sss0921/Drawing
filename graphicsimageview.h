/**************************************************************************
**
** Copyright (C) 2019 sss0921.
** Contact: sss09217313@163.com
**
** This file is part of Drawing.
**
**************************************************************************/

#pragma once

#include <QGraphicsView>

class GraphicsImageScene;
class GraphicsImageView : public QGraphicsView
{
public:
    GraphicsImageView(QWidget *parent = nullptr);

    QImage image() const;
    void setImage(const QImage &image);

private:
    GraphicsImageScene *m_graphicsImageScene;
};
