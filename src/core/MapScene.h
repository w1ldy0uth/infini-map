#ifndef MAPSCENE_H
#define MAPSCENE_H
#pragma once

#include <QGraphicsScene>
#include <QImage>
#include <QPixmap>

class MapScene : public QGraphicsScene
{
    Q_OBJECT

public:
    MapScene(QObject* parent = nullptr);
    void generateTerrain();

private:
    int width  = 2048;
    int height = 2048;
    QImage terrainImage;
    QPixmap terrainPixmap;
};

#endif
