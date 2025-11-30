#ifndef BIOMECOLOR_H
#define BIOMECOLOR_H
#pragma once

#include <QColor>

// Convert height from fBm to biome color
class BiomeColor
{
public:
    static QRgb getColor(float height);
};

#endif
