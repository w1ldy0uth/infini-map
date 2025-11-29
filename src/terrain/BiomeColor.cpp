#include "BiomeColor.h"
#include <QtMath>

QRgb BiomeColor::getColor(float height)
{
    height = qBound(0.0f, height, 1.0f);

    if (height < 0.30f) {
        // Deep Ocean to Shallow Sea
        float t = height / 0.30f;
        int r = 0;
        int g = 20 + static_cast<int>(t * 40);
        int b = 80 + static_cast<int>(t * 100);
        return qRgb(r, g, b);
    }
    else if (height < 0.32f) {
        // Sandy Beach
        float t = (height - 0.30f) / 0.02f;
        int r = 200 + static_cast<int>(t * 55);
        int g = 190 + static_cast<int>(t * 40);
        int b = 100 - static_cast<int>(t * 80);
        return qRgb(r, g, b);
    }
    else if (height < 0.50f) {
        // Plains to Grassland
        float t = (height - 0.32f) / 0.18f;
        int r = 100 + static_cast<int>(t * 60);
        int g = 150 + static_cast<int>(t * 70);
        int b = 50 + static_cast<int>(t * 30);
        return qRgb(r, g, b);
    }
    else if (height < 0.65f) {
        // Forest (darker green)
        float t = (height - 0.50f) / 0.15f;
        int r = 30 + static_cast<int>(t * 40);
        int g = 90 + static_cast<int>(t * 60);
        int b = 30 + static_cast<int>(t * 30);
        return qRgb(r, g, b);
    }
    else if (height < 0.80f) {
        // Mountains (rocky, desaturated)
        float t = (height - 0.65f) / 0.15f;
        int r = 110 + static_cast<int>(t * 40);
        int g = 105 + static_cast<int>(t * 35);
        int b = 100 + static_cast<int>(t * 30);
        return qRgb(r, g, b);
    }
    else {
        // Snow (bright white with soft gray)
        float t = (height - 0.80f) / 0.20f;
        int val = 230 + static_cast<int>(t * 25);
        return qRgb(val, val, val);
    }
}
