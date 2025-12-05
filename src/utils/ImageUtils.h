#pragma once

#include <QImage>
#include <QDebug>

// Simple image filtering utilities
class ImageUtils
{
public:
    static QImage gaussianBlur(const QImage& image, int radius = 1);
};
