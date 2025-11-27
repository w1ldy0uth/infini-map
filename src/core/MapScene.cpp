#include "MapScene.h"
#include "Noise.h"
#include "BiomeColor.h"
#include <QGraphicsPixmapItem>

MapScene::MapScene(QObject* parent)
    : QGraphicsScene(parent)
{
    setSceneRect(0, 0, width, height);
    generateTerrain();
}

void MapScene::generateTerrain()
{
    terrainImage = QImage(width, height, QImage::Format_RGB32);

    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            float value = Noise::normalizedValue2D(x, y, 1234);
            QRgb color = BiomeColor::getColor(value);
            terrainImage.setPixel(x, y, color);
        }
    }

    terrainPixmap = QPixmap::fromImage(terrainImage);
    addPixmap(terrainPixmap);
}

