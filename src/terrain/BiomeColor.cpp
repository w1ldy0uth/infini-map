#include "BiomeColor.h"

// Map height [0..1] to biome color
QRgb BiomeColor::getColor(float height)
{
    // Clamped height
    if (height < 0.0f) height = 0.0f;
    if (height > 1.0f) height = 1.0f;

    QRgb color;

    if (height < 0.30f) {
        // Water — deep to shallow
        float t = height / 0.30f;
        int r = 0;
        int g = 64 + static_cast<int>(t * 64);      // 64 → 128
        int b = 128 + static_cast<int>(t * 127);    // 128 → 255
        color = qRgb(r, g, b);
    }
    else if (height < 0.50f) {
        // Sandy beach / coast
        float t = (height - 0.30f) / 0.20f;
        int r = 240 + static_cast<int>(t * 15);
        int g = 230 + static_cast<int>(t * 25);
        int b = 160 - static_cast<int>(t * 60);
        color = qRgb(r, g, b);
    }
    else if (height < 0.70f) {
        // Plains / forests
        float t = (height - 0.50f) / 0.20f;
        int r = 30 + static_cast<int>(t * 40);
        int g = 100 + static_cast<int>(t * 75);
        int b = 30 + static_cast<int>(t * 40);
        color = qRgb(r, g, b);
    }
    else if (height < 0.90f) {
        // Mountains — rocky browns
        float t = (height - 0.70f) / 0.20f;
        int r = 90 + static_cast<int>(t * 40);
        int g = 80 + static_cast<int>(t * 30);
        int b = 70 + static_cast<int>(t * 30);
        color = qRgb(r, g, b);
    }
    else {
        // Snow — white with gray hint
        float t = (height - 0.90f) / 0.10f;
        int base = 230;
        int variation = static_cast<int>(t * 25);
        int val = base + variation;
        color = qRgb(val, val, val);
    }

    return color;
}
