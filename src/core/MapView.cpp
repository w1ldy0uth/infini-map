#include "MapView.h"
#include "config/Config.h"
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
    if (event->angleDelta().y() > 0) {
        zoom(Config::ZoomInFactor);
    } else {
        zoom(Config::ZoomOutFactor);
    }
}

void MapView::zoom(double factor)
{
    // Validate zoom factor
    if (factor <= 0.0) {
        qWarning() << "Invalid zoom factor (must be positive):" << factor;
        return;
    }

    if (factor < 0.1 || factor > 10.0) {
        qWarning() << "Zoom factor outside reasonable range [0.1, 10.0]:" << factor;
        // Allow but warn
    }

    const double currentScale = transform().m11();
    const double newScale = currentScale * factor;

    // Bounds checking with floating point tolerance
    if (newScale >= Config::MinZoomScale - 1e-6 && newScale <= Config::MaxZoomScale + 1e-6) {
        scale(factor, factor);
    } else {
        qDebug() << "Zoom request out of bounds - current:" << currentScale
                 << "requested:" << newScale
                 << "allowed: [" << Config::MinZoomScale << "," << Config::MaxZoomScale << "]";
    }
}
