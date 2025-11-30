#include "MapScene.h"
#include "terrain/Noise.h"
#include "terrain/BiomeColor.h"
#include "utils/ImageUtils.h"
#include "utils/Random.h"
#include <QGraphicsPixmapItem>
#include <QDebug>

MapScene::MapScene(QObject* parent)
    : QGraphicsScene(parent)
{
    setSceneRect(0, 0, width, height);
    realSeed = generateRandomSeed();
    generateTerrain();
}

void MapScene::generateTerrain()
{
    terrainImage = QImage(width, height, QImage::Format_RGB32);
    if (terrainImage.isNull()) {
        qDebug() << "Failed to create image!";
        return;
    }

    constexpr float noiseRange = Config::NoiseCeil - Config::NoiseFloor;

    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            float nx = x * Config::NoiseScale;
            float ny = y * Config::NoiseScale;
            float noise = Noise::normalizedValue2D(nx, ny, realSeed);

            float value = (noise - Config::NoiseFloor) / noiseRange;
            value = qBound(0.0f, value, 1.0f);

            QRgb color = BiomeColor::getColor(value);
            terrainImage.setPixel(x, y, color);
        }
    }

    terrainImage = ImageUtils::gaussianBlur(terrainImage, Config::BlurRadius);
    // terrainImage.fill(qRgb(0, 128, 255)); solid ocean (for tests)

    terrainPixmap = QPixmap::fromImage(terrainImage);
    addPixmap(terrainPixmap);

    qDebug() << "Terrain generated:" << width << "x" << height;
}
