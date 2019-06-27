/**************************************************************************
**
** Copyright (C) 2019 sss0921.
** Contact: sss09217313@163.com
**
** This file is part of Drawing.
**
**************************************************************************/

#pragma once

#include "graphicsimagescene.h"
#include "graphicswheelview.h"

class GraphicsImageView : public GraphicsWheelView
{
public:
    GraphicsImageView(QWidget *parent = nullptr);

    GraphicsImageScene::Mode mode() const;
    void setMode(GraphicsImageScene::Mode mode);

    QImage image() const;
    void setImage(const QImage &image);

private:
    GraphicsImageScene *m_graphicsImageScene;
};
