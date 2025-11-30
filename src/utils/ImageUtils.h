#ifndef IMAGEUTILS_H
#define IMAGEUTILS_H
#pragma once

#include <QImage>

// Simple image filtering utilities
class ImageUtils
{
public:
    static QImage gaussianBlur(const QImage& image, int radius = 1);
};

#endif
