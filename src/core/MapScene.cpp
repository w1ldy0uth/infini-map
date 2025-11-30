#include "core/MapScene.h"
#include "terrain/Noise.h"
#include "terrain/BiomeColor.h"
#include "utils/ImageUtils.h"
#include <QGraphicsPixmapItem>
#include <QDebug>

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

    constexpr float noiseMin = 0.272f;
    constexpr float noiseMax = 0.714f;
    constexpr float noiseRange = noiseMax - noiseMin;
    constexpr float baseScale = 0.55f;

    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            float nx = x * baseScale;
            float ny = y * baseScale;
            float noise = Noise::normalizedValue2D(nx, ny, 1234);

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
