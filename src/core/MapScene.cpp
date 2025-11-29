#include <QGraphicsPixmapItem>
#include "MapScene.h"
#include "Noise.h"
#include "BiomeColor.h"
#include "ImageUtils.h"

MapScene::MapScene(QObject* parent)
    : QGraphicsScene(parent)
{
    setSceneRect(0, 0, width, height);
    generateTerrain();
}

void MapScene::generateTerrain()
{
    terrainImage = QImage(width, height, QImage::Format_RGB32);
    if (terrainImage.isNull()) {
        qDebug() << "Failed to create image!";
        return;
    }

    const float noiseMin = 0.272f;
    const float noiseMax = 0.714f;
    const float noiseRange = noiseMax - noiseMin;
    const float baseScale = 0.55f;

    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            float nx = x;
            float ny = y;
            float noise = Noise::normalizedValue2D(nx * baseScale, ny * baseScale, 1234);

            float value = (noise - noiseMin) / noiseRange;
            value = qBound(0.0f, value, 1.0f);

            QRgb color = BiomeColor::getColor(value);
            terrainImage.setPixel(x, y, color);
        }
    }

    terrainImage = ImageUtils::gaussianBlur(terrainImage, 1);
    // terrainImage.fill(qRgb(0, 128, 255)); solid ocean (for tests)

    terrainPixmap = QPixmap::fromImage(terrainImage);
    addPixmap(terrainPixmap);

    qDebug() << "Terrain generated:" << width << "x" << height;
}
