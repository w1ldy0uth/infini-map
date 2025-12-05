#include "MapScene.h"
#include "terrain/Noise.h"
#include "terrain/BiomeColor.h"
#include "utils/ImageUtils.h"
#include "utils/Random.h"
#include <QGraphicsPixmapItem>
#include <QDebug>
#include <QtConcurrent/QtConcurrent>
#include <QThread>

MapScene::MapScene(QObject *parent)
    : QGraphicsScene(parent)
{
    setSceneRect(0, 0, width, height);
    realSeed = generateRandomSeed();
    qDebug() << "Seed:" << realSeed;
    generateTerrain();
}

void MapScene::generateTerrain()
{
    // Validate configuration
    constexpr float noiseRange = Config::NoiseCeil - Config::NoiseFloor;
    if (noiseRange <= 0.0f) {
        qWarning() << "Invalid noise configuration: NoiseCeil must be greater than NoiseFloor";
        return;
    }

    // Create terrain image
    terrainImage = QImage(width, height, QImage::Format_RGB32);
    if (terrainImage.isNull()) {
        qCritical() << "Failed to create terrain image of size" << width << "x" << height;
        return;
    }

    if (terrainImage.width() != width || terrainImage.height() != height) {
        qCritical() << "Created image dimensions don't match requested size";
        return;
    }

    // Use parallel processing for terrain generation
    QVector<QFuture<void>> futures;

    // Process image in row chunks for better parallelization
    const int numThreads = QThread::idealThreadCount();
    const int rowsPerThread = (height + numThreads - 1) / numThreads;

    for (int threadId = 0; threadId < numThreads; ++threadId) {
        const int startY = threadId * rowsPerThread;
        const int endY = qMin(startY + rowsPerThread, height);

        futures.append(QtConcurrent::run([this, startY, endY, noiseRange]() {
            for (int y = startY; y < endY; ++y) {
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
        }));
    }

    // Wait for all threads to complete
    for (auto& future : futures) {
        future.waitForFinished();
    }

    // Apply blur effect
    terrainImage = ImageUtils::gaussianBlur(terrainImage, Config::BlurRadius);
    if (terrainImage.isNull()) {
        qCritical() << "Gaussian blur failed, terrain image became invalid";
        return;
    }

    // Convert to pixmap for display
    terrainPixmap = QPixmap::fromImage(terrainImage);
    if (terrainPixmap.isNull()) {
        qCritical() << "Failed to convert terrain image to pixmap";
        return;
    }

    // Add to scene
    if (!addPixmap(terrainPixmap)) {
        qCritical() << "Failed to add terrain pixmap to scene";
        return;
    }

    qInfo() << "Terrain generated successfully:" << width << "x" << height << "pixels";
}
