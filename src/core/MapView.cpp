#include "MapView.h"
#include <QWheelEvent>
#include <QPainter>

MapView::MapView(QWidget* parent)
    : QGraphicsView(parent)
{
    setRenderHint(QPainter::Antialiasing, true);
    setRenderHint(QPainter::TextAntialiasing, true);
    setRenderHint(QPainter::SmoothPixmapTransform, true);

    setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
    setResizeAnchor(QGraphicsView::AnchorUnderMouse);
    setViewportUpdateMode(QGraphicsView::SmartViewportUpdate);
    setDragMode(QGraphicsView::ScrollHandDrag);

    setOptimizationFlag(QGraphicsView::DontSavePainterState, true);
    setOptimizationFlag(QGraphicsView::IndirectPainting, true);
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
