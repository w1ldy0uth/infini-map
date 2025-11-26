#include "MapScene.h"
#include <QGraphicsRectItem>

MapScene::MapScene(QObject* parent)
    : QGraphicsScene(parent)
{
    setSceneRect(0, 0, width, height);
    paintTerrain();
}

void MapScene::paintTerrain()
{
    for (int x = 0; x < width; x += 64) {
        for (int y = 0; y < height; y += 64) {
            auto* item = addRect(x, y, 64, 64);
            item->setBrush(Qt::GlobalColor::darkGreen);
            item->setPen(Qt::NoPen);
        }
    }
}
