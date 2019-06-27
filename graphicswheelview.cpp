/**************************************************************************
**
** Copyright (C) 2019 sss0921.
** Contact: sss09217313@163.com
**
** This file is part of Drawing.
**
**************************************************************************/

#include "graphicswheelview.h"

#include <QWheelEvent>

class GraphicsWheelViewPrivate
{
public:
    GraphicsWheelViewPrivate(GraphicsWheelView *q);
    ~GraphicsWheelViewPrivate();
    void dealWithScaleChanged(double rSacle, bool causedByWheel = true);

    double scale{ 1 }; // on work when view rotate 0, 90, 180, 270
    double scaleMin{ 0.01 };
    double scaleMax{ 64 };
    GraphicsWheelView::WheelBehavior wheelBehavior{
        GraphicsWheelView::WheelBehavior::WheelUpZoomIn
    };

    GraphicsWheelView *q;
};

GraphicsWheelViewPrivate::GraphicsWheelViewPrivate(GraphicsWheelView *q)
    : q(q)
{
}

GraphicsWheelViewPrivate::~GraphicsWheelViewPrivate()
{
}

void GraphicsWheelViewPrivate::dealWithScaleChanged(double rScale, bool causedByWheel)
{
    if (fabs(rScale - 1) < 10e-4)
        return;

    if (causedByWheel)
        q->setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
    else
        q->setTransformationAnchor(QGraphicsView::AnchorViewCenter);

    q->scale(rScale, rScale);
    scale = qMax(fabs(q->transform().m11()), fabs(q->transform().m12()));
    emit q->scaleChanged(scale);
}

GraphicsWheelView::GraphicsWheelView(QWidget *parent)
    : GraphicsWheelView(nullptr, parent)
{
}

GraphicsWheelView::GraphicsWheelView(QGraphicsScene *scene, QWidget *parent)
    : QGraphicsView(scene, parent)
    , d(new GraphicsWheelViewPrivate(this))
{
    setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);
}

GraphicsWheelView::~GraphicsWheelView()
{
}

double GraphicsWheelView::currentScale() const
{
    return d->scale;
}

GraphicsWheelView::WheelBehavior GraphicsWheelView::wheelBehavior() const
{
    return d->wheelBehavior;
}

void GraphicsWheelView::setWheelBehavior(WheelBehavior behavior)
{
    d->wheelBehavior = behavior;
}

void GraphicsWheelView::setCurrentScale(double factor)
{
    if (factor > d->scaleMax)
        factor = d->scaleMax;
    else if (factor < d->scaleMin)
        factor = d->scaleMin;

    d->dealWithScaleChanged(factor / currentScale(), false);
}

void GraphicsWheelView::setScaleRange(double min, double max)
{
    d->scaleMin = min;
    d->scaleMax = max;
    if (currentScale() < d->scaleMin)
        setCurrentScale(d->scaleMin);
    else if (currentScale() > d->scaleMax)
        setCurrentScale(d->scaleMax);
}

void GraphicsWheelView::autoFit(const QRectF &rect, Qt::AspectRatioMode mode)
{
    Q_ASSERT(mode == Qt::KeepAspectRatio || mode == Qt::KeepAspectRatioByExpanding);
    fitInView(rect, mode);
    d->scale = qMax(fabs(transform().m11()), fabs(transform().m12()));
    emit scaleChanged(d->scale);
}

void GraphicsWheelView::wheelEvent(QWheelEvent *event)
{
    if (d->wheelBehavior == WheelBehavior::NoWheel)
        return;
    if (d->wheelBehavior == WheelBehavior::QGraphicsViewDefault) {
        QGraphicsView::wheelEvent(event);
        return;
    }

    // default is WheelBehavior::WheelUpZoomIn
    double numDegrees = event->delta() / 8.0;
    if (d->wheelBehavior == WheelBehavior::WheelUpZoomOut)
        numDegrees *= -1;

    double numSteps = numDegrees / 15.0;
    double factor = pow(1.125, numSteps);

    if (numSteps > 0)
        factor = qMin(factor, d->scaleMax / currentScale());
    else
        factor = qMax(factor, d->scaleMin / currentScale());

    d->dealWithScaleChanged(factor, true);
}
