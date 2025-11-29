#include "ImageUtils.h"
#include <QtMath>

QImage ImageUtils::gaussianBlur(const QImage& image, int radius)
{
    if (radius <= 0) return image;

    QImage blurred = image.copy();
    int w = image.width();
    int h = image.height();

    int kernelSize = radius * 2 + 1;
    float* kernel = new float[kernelSize];
    for (int i = 0; i < kernelSize; ++i) {
        float x = i - radius;
        kernel[i] = expf(-x * x / (2 * 1.5f * 1.5f));
    }

    QImage temp = image.copy();
    for (int y = 0; y < h; ++y) {
        for (int x = 0; x < w; ++x) {
            float r = 0, g = 0, b = 0, weightSum = 0;
            for (int k = 0; k < kernelSize; ++k) {
                int sx = x + k - radius;
                if (sx < 0 || sx >= w) continue;
                QRgb pixel = temp.pixel(sx, y);
                float w = kernel[k];
                r += qRed(pixel)   * w;
                g += qGreen(pixel) * w;
                b += qBlue(pixel)  * w;
                weightSum += w;
            }
            r /= weightSum; g /= weightSum; b /= weightSum;
            blurred.setPixel(x, y, qRgb((int)r, (int)g, (int)b));
        }
    }

    // Vertical pass
    temp = blurred.copy();
    for (int y = 0; y < h; ++y) {
        for (int x = 0; x < w; ++x) {
            float r = 0, g = 0, b = 0, weightSum = 0;
            for (int k = 0; k < kernelSize; ++k) {
                int sy = y + k - radius;
                if (sy < 0 || sy >= h) continue;
                QRgb pixel = temp.pixel(x, sy);
                float w = kernel[k];
                r += qRed(pixel)   * w;
                g += qGreen(pixel) * w;
                b += qBlue(pixel)  * w;
                weightSum += w;
            }
            r /= weightSum; g /= weightSum; b /= weightSum;
            blurred.setPixel(x, y, qRgb((int)r, (int)g, (int)b));
        }
    }

    delete[] kernel;
    return blurred;
}
