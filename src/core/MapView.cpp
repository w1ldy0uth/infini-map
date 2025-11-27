#include "MapView.h"
#include <QWheelEvent>

MapView::MapView(QWidget* parent)
    : QGraphicsView(parent)
{
    setRenderHint(QPainter::RenderHint::Antialiasing, false);
    setDragMode(QGraphicsView::ScrollHandDrag);
    setOptimizationFlag(QGraphicsView::DontAdjustForAntialiasing, true);
    setViewportUpdateMode(QGraphicsView::SmartViewportUpdate);
    setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
}

void MapView::wheelEvent(QWheelEvent* event)
{
    const double zoomInFactor = 1.25;
    const double zoomOutFactor = 1 / zoomInFactor;

    if (event->angleDelta().y() > 0) {
        zoom(zoomInFactor);
    } else {
        zoom(zoomOutFactor);
    }
}

void MapView::zoom(double factor)
{
    const double currentScale = transform().m11();
    const double minScale = 0.1;
    const double maxScale = 10.0;

    if (currentScale * factor >= minScale && currentScale * factor <= maxScale) {
        scale(factor, factor);
    }
}
