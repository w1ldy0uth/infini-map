#ifndef MAPSCENE_H
#define MAPSCENE_H
#pragma once

#include <config/Config.h>
#include <QGraphicsScene>

// Terrain map scene with procedural generation
class MapScene : public QGraphicsScene
{
    Q_OBJECT

public:
    MapScene(QObject* parent = nullptr);
    void generateTerrain();
    int currentSeed() const;

private:
    int realSeed;
    static constexpr int width  = Config::MapWidth;
    static constexpr int height = Config::MapHeight;

    QImage terrainImage;
    QPixmap terrainPixmap;
};

#endif
