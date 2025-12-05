#pragma once

#include <QColor>
#include <QDebug>

// Convert height from fBm to biome color
class BiomeColor
{
public:
    static QRgb getColor(float height);
};
