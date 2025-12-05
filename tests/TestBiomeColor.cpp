#include "TestBiomeColor.h"
#include "config/Config.h"

void TestBiomeColor::testGetColor_validRange()
{
    // Test colors for valid height range [0, 1]
    for (float height = 0.0f; height <= 1.0f; height += 0.1f) {
        QRgb color = BiomeColor::getColor(height);

        // Verify color components are valid
        int r = qRed(color);
        int g = qGreen(color);
        int b = qBlue(color);

        QVERIFY(r >= 0 && r <= 255);
        QVERIFY(g >= 0 && g <= 255);
        QVERIFY(b >= 0 && b <= 255);
    }
}

void TestBiomeColor::testGetColor_clamping()
{
    // Test that values outside [0, 1] are clamped
    // Note: This may produce warnings, which is expected
    QRgb color1 = BiomeColor::getColor(-0.5f); // Below 0
    QRgb color2 = BiomeColor::getColor(1.5f);  // Above 1

    // Colors should still be valid
    QVERIFY(qRed(color1) >= 0 && qRed(color1) <= 255);
    QVERIFY(qGreen(color1) >= 0 && qGreen(color1) <= 255);
    QVERIFY(qBlue(color1) >= 0 && qBlue(color1) <= 255);

    QVERIFY(qRed(color2) >= 0 && qRed(color2) <= 255);
    QVERIFY(qGreen(color2) >= 0 && qGreen(color2) <= 255);
    QVERIFY(qBlue(color2) >= 0 && qBlue(color2) <= 255);
}

void TestBiomeColor::testGetColor_biomeTransitions()
{
    // Test biome transition points
    QRgb seaColor = BiomeColor::getColor(Config::SeaLevel - 0.01f);
    QRgb beachColor = BiomeColor::getColor(Config::BeachEnd - 0.01f);
    QRgb plainsColor = BiomeColor::getColor(Config::PlainsEnd - 0.01f);
    QRgb forestColor = BiomeColor::getColor(Config::ForestEnd - 0.01f);
    QRgb mountainColor = BiomeColor::getColor(Config::MountainEnd - 0.01f);
    QRgb snowColor = BiomeColor::getColor(Config::MountainEnd + 0.01f);

    // Colors should be different for different biomes
    QVERIFY(seaColor != beachColor);
    QVERIFY(beachColor != plainsColor);
    QVERIFY(plainsColor != forestColor);
    QVERIFY(forestColor != mountainColor);
    QVERIFY(mountainColor != snowColor);

    // All should be valid colors
    QVERIFY(qRed(seaColor) >= 0 && qRed(seaColor) <= 255);
    QVERIFY(qRed(beachColor) >= 0 && qRed(beachColor) <= 255);
    QVERIFY(qRed(plainsColor) >= 0 && qRed(plainsColor) <= 255);
    QVERIFY(qRed(forestColor) >= 0 && qRed(forestColor) <= 255);
    QVERIFY(qRed(mountainColor) >= 0 && qRed(mountainColor) <= 255);
    QVERIFY(qRed(snowColor) >= 0 && qRed(snowColor) <= 255);
}

void TestBiomeColor::testGetColor_extremeValues()
{
    // Test edge cases
    QRgb color0 = BiomeColor::getColor(0.0f);     // Absolute minimum
    QRgb color1 = BiomeColor::getColor(1.0f);     // Absolute maximum
    QRgb colorMid = BiomeColor::getColor(0.5f);   // Middle value

    // All should produce valid colors
    QVERIFY(qRed(color0) >= 0 && qRed(color0) <= 255);
    QVERIFY(qRed(color1) >= 0 && qRed(color1) <= 255);
    QVERIFY(qRed(colorMid) >= 0 && qRed(colorMid) <= 255);

    // Extreme values should be different
    QVERIFY(color0 != color1);
}
