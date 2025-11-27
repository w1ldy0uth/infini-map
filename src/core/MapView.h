#ifndef MAPVIEW_H
#define MAPVIEW_H
#pragma once

#include <QGraphicsView>

class MapView : public QGraphicsView
{
    Q_OBJECT

public:
    MapView(QWidget* parent = nullptr);

protected:
    void wheelEvent(QWheelEvent* event) override;

private:
    void zoom(double factor);
};

#endif
