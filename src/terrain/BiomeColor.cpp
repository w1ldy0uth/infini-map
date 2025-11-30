#include "BiomeColor.h"
#include "config/Config.h"
#include <QtMath>

QRgb BiomeColor::getColor(float height)
{
    height = qBound(0.0f, height, 1.0f);

    if (height < Config::SeaLevel) {
        // Ocean
        float t = height / Config::SeaLevel;
        int r = 0;
        int g = 20 + static_cast<int>(t * 40);
        int b = 80 + static_cast<int>(t * 100);
        return qRgb(r, g, b);
    }
    if (height < Config::BeachEnd) {
        // Beach
        float t = (height - Config::SeaLevel) / (Config::BeachEnd - Config::SeaLevel);
        int r = 200 + static_cast<int>(t * 55);
        int g = 190 + static_cast<int>(t * 40);
        int b = 100 - static_cast<int>(t * 80);
        return qRgb(r, g, b);
    }
    if (height < Config::PlainsEnd) {
        // Plains
        float t = (height - Config::BeachEnd) / (Config::PlainsEnd - Config::BeachEnd);
        int r = 100 + static_cast<int>(t * 60);
        int g = 150 + static_cast<int>(t * 70);
        int b = 50 + static_cast<int>(t * 30);
        return qRgb(r, g, b);
    }
    if (height < Config::ForestEnd) {
        // Forest
        float t = (height - Config::PlainsEnd) / (Config::ForestEnd - Config::PlainsEnd);
        int r = 30 + static_cast<int>(t * 40);
        int g = 90 + static_cast<int>(t * 60);
        int b = 30 + static_cast<int>(t * 30);
        return qRgb(r, g, b);
    }
    if (height < Config::MountainEnd) {
        // Mountains
        float t = (height - Config::ForestEnd) / (Config::MountainEnd - Config::ForestEnd);
        int r = 110 + static_cast<int>(t * 40);
        int g = 105 + static_cast<int>(t * 35);
        int b = 100 + static_cast<int>(t * 30);
        return qRgb(r, g, b);
    }
    // Snow
    float t = (height - Config::MountainEnd) / (1.0f - Config::MountainEnd);
    int val = 230 + static_cast<int>(t * 25);
    return qRgb(val, val, val);
}
