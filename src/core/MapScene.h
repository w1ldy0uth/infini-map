#ifndef MAPSCENE_H
#define MAPSCENE_H
#pragma once

#include <QGraphicsScene>

// Terrain map scene with procedural generation
class MapScene : public QGraphicsScene
{
    Q_OBJECT

public:
    MapScene(QObject* parent = nullptr);
    void generateTerrain();

private:
    static constexpr int width  = 2048;
    static constexpr int height = 2048;

    QImage terrainImage;
    QPixmap terrainPixmap;
};

#endif
