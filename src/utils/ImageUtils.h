#ifndef IMAGEUTILS_H
#define IMAGEUTILS_H

#include <QImage>

class ImageUtils
{
public:
    static QImage gaussianBlur(const QImage& image, int radius = 1);
};

#endif
