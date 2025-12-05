#include "ImageUtils.h"
#include "config/Config.h"
#include <QVarLengthArray>
#include <QtMath>

// Optimized Gaussian blur using separable convolution
QImage ImageUtils::gaussianBlur(const QImage& image, int radius)
{
    // Validate input parameters
    if (radius < 0) {
        qWarning() << "Gaussian blur radius cannot be negative:" << radius;
        return image;
    }

    if (radius > 50) {
        qWarning() << "Gaussian blur radius too large:" << radius << "(max recommended: 50)";
        // Allow but warn for very large radii
    }

    // Validate input
    if (image.isNull()) {
        qWarning() << "Gaussian blur called with null image";
        return QImage();
    }

    if (radius == 0) {
        return image;
    }

    const int w = image.width();
    const int h = image.height();

    // Check for valid dimensions
    if (w <= 0 || h <= 0) {
        qWarning() << "Gaussian blur called with invalid image dimensions:" << w << "x" << h;
        return QImage();
    }

    const int kSize = radius * 2 + 1;

    // Pre-compute Gaussian kernel for better performance
    QVarLengthArray<float> kernel(kSize);
    const float sigma = radius / Config::BlurSigmaDivisor;
    const float sigma2 = 2.0f * sigma * sigma;

    float sum = 0.0f;
    for (int i = 0; i < kSize; ++i) {
        float x = i - radius;
        float val = expf(-x * x / sigma2);
        kernel[i] = val;
        sum += val;
    }

    // Check for kernel generation failure
    if (sum <= 0.0f) {
        qWarning() << "Gaussian kernel generation failed: sum is zero or negative";
        return image; // Return original image as fallback
    }

    // Normalize kernel
    for (int i = 0; i < kSize; ++i) {
        kernel[i] /= sum;
    }

    // Convert to RGB32 format for processing
    QImage workImage = image.convertToFormat(QImage::Format_RGB32);
    if (workImage.isNull()) {
        qWarning() << "Image format conversion failed in gaussian blur";
        return image;
    }

    // Use scan lines for faster pixel access
    if (workImage.bytesPerLine() != w * 4) {
        qWarning() << "Unexpected image format - falling back to pixel access";
        // Continue with pixel access as fallback
    }

    QImage result(w, h, QImage::Format_RGB32);
    if (result.isNull()) {
        qWarning() << "Failed to create result image for gaussian blur";
        return image;
    }

    // Horizontal pass - blur each row
    for (int y = 0; y < h; ++y) {
        const QRgb* srcLine = reinterpret_cast<const QRgb*>(workImage.scanLine(y));
        QRgb* dstLine = reinterpret_cast<QRgb*>(result.scanLine(y));

        for (int x = 0; x < w; ++x) {
            float r = 0, g = 0, b = 0, weightSum = 0;

            for (int k = 0; k < kSize; ++k) {
                int sx = x + k - radius;
                if (sx >= 0 && sx < w) {
                    QRgb pix = srcLine[sx];
                    float w = kernel[k];
                    r += qRed(pix)   * w;
                    g += qGreen(pix) * w;
                    b += qBlue(pix)  * w;
                    weightSum += w;
                }
            }

            // WeightSum should always be > 0 for valid kernel, but check anyway
            if (weightSum > 0.0f) {
                dstLine[x] = qRgb(qBound(0, (int)(r / weightSum), 255),
                                qBound(0, (int)(g / weightSum), 255),
                                qBound(0, (int)(b / weightSum), 255));
            } else {
                dstLine[x] = srcLine[x]; // Fallback
            }
        }
    }

    // Vertical pass - blur each column using the horizontal result
    workImage = result; // Reuse workImage for intermediate result
    result = QImage(w, h, QImage::Format_RGB32);
    if (result.isNull()) {
        qWarning() << "Failed to create result image for vertical blur pass";
        return image;
    }

    for (int y = 0; y < h; ++y) {
        QRgb* dstLine = reinterpret_cast<QRgb*>(result.scanLine(y));

        for (int x = 0; x < w; ++x) {
            float r = 0, g = 0, b = 0, weightSum = 0;

            for (int k = 0; k < kSize; ++k) {
                int sy = y + k - radius;
                if (sy >= 0 && sy < h) {
                    const QRgb* srcLine = reinterpret_cast<const QRgb*>(workImage.scanLine(sy));
                    QRgb pix = srcLine[x];
                    float w = kernel[k];
                    r += qRed(pix)   * w;
                    g += qGreen(pix) * w;
                    b += qBlue(pix)  * w;
                    weightSum += w;
                }
            }

            if (weightSum > 0.0f) {
                dstLine[x] = qRgb(qBound(0, (int)(r / weightSum), 255),
                                qBound(0, (int)(g / weightSum), 255),
                                qBound(0, (int)(b / weightSum), 255));
            } else {
                const QRgb* srcLine = reinterpret_cast<const QRgb*>(workImage.scanLine(y));
                dstLine[x] = srcLine[x]; // Fallback
            }
        }
    }

    // Final validation
    if (result.isNull() || result.width() != w || result.height() != h) {
        qWarning() << "Gaussian blur produced invalid result";
        return image; // Return original image as fallback
    }

    return result;
}

