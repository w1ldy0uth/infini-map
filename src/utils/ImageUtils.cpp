#include "ImageUtils.h"
#include <QVarLengthArray>
#include <QtMath>

// Fast Gaussian blur (radius >= 1)
QImage ImageUtils::gaussianBlur(const QImage& image, int radius)
{
    if (radius <= 0)
        return image;

    const int w = image.width();
    const int h = image.height();
    const int kSize = radius * 2 + 1;

    // Stack-allocated kernel
    QVarLengthArray<float> kernel(kSize);
    const float sigma = 1.5f;
    const float sigma2 = 2.0f * sigma * sigma;

    float sum = 0.0f;
    for (int i = 0; i < kSize; ++i) {
        float x = i - radius;
        float val = expf(-x * x / sigma2);
        kernel[i] = val;
        sum += val;
    }

    // Normalize
    for (int i = 0; i < kSize; ++i)
        kernel[i] /= sum;

    QImage result = image.convertToFormat(QImage::Format_RGB32);

    // Horizontal pass
    QImage temp = result;
    for (int y = 0; y < h; ++y) {
        for (int x = 0; x < w; ++x) {
            float r = 0, g = 0, b = 0, weightSum = 0;
            for (int k = 0; k < kSize; ++k) {
                int sx = x + k - radius;
                if (sx < 0 || sx >= w) continue;
                QRgb pix = temp.pixel(sx, y);
                float w = kernel[k];
                r += qRed(pix)   * w;
                g += qGreen(pix) * w;
                b += qBlue(pix)  * w;
                weightSum += w;
            }
            r /= weightSum; g /= weightSum; b /= weightSum;
            result.setPixel(x, y, qRgb((int)r, (int)g, (int)b));
        }
    }

    // Vertical pass
    temp = result;
    for (int y = 0; y < h; ++y) {
        for (int x = 0; x < w; ++x) {
            float r = 0, g = 0, b = 0, weightSum = 0;
            for (int k = 0; k < kSize; ++k) {
                int sy = y + k - radius;
                if (sy < 0 || sy >= h) continue;
                QRgb pix = temp.pixel(x, sy);
                float w = kernel[k];
                r += qRed(pix)   * w;
                g += qGreen(pix) * w;
                b += qBlue(pix)  * w;
                weightSum += w;
            }
            r /= weightSum; g /= weightSum; b /= weightSum;
            result.setPixel(x, y, qRgb((int)r, (int)g, (int)b));
        }
    }

    return result;
}
