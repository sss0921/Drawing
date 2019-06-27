/**************************************************************************
**
** Copyright (C) 2019 sss0921.
** Contact: sss09217313@163.com
**
** This file is part of Drawing.
**
**************************************************************************/

#pragma once

#include <memory>
#include <QGraphicsView>

class GraphicsWheelViewPrivate;
class GraphicsWheelView : public QGraphicsView
{
    Q_OBJECT
public:
    enum class WheelBehavior {
        NoWheel, //! No Wheel
        QGraphicsViewDefault, //! Default behavior of QGraphicsView
        WheelUpZoomIn, //! Zoom in the scene when wheel up
        WheelUpZoomOut //! Zoom out the scene when wheel up
    };

    GraphicsWheelView(QWidget *parent = nullptr);
    GraphicsWheelView(QGraphicsScene *scene, QWidget *parent = nullptr);
    ~GraphicsWheelView() override;

    double currentScale() const;
    WheelBehavior wheelBehavior() const;

public slots:
    void setWheelBehavior(WheelBehavior behavior);
    void setCurrentScale(double factor);
    void setScaleRange(double min, double max);
    void autoFit(const QRectF &rect, Qt::AspectRatioMode mode);

signals:
    void scaleChanged(double scale);

protected:
    void wheelEvent(QWheelEvent *event) override;

private:
    std::unique_ptr<GraphicsWheelViewPrivate> d;
};
