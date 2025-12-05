#include "TestConfig.h"

void TestConfig::testMapDimensions()
{
    // Test map dimensions are positive and reasonable
    QVERIFY(Config::MapWidth > 0);
    QVERIFY(Config::MapHeight > 0);
    QVERIFY(Config::MapWidth <= 8192);  // Reasonable upper limit
    QVERIFY(Config::MapHeight <= 8192); // Reasonable upper limit
}

void TestConfig::testNoiseParameters()
{
    // Test noise octave count
    QVERIFY(Config::NoiseOctaves >= 1);
    QVERIFY(Config::NoiseOctaves <= 12);

    // Test noise persistence (controls amplitude decay)
    QVERIFY(Config::NoisePersistence > 0.0f);
    QVERIFY(Config::NoisePersistence <= 1.0f);

    // Test noise lacunarity (controls frequency multiplier)
    QVERIFY(Config::NoiseLacunarity >= 1.1f);
    QVERIFY(Config::NoiseLacunarity <= 10.0f);

    // Test noise base frequency
    QVERIFY(Config::NoiseBaseFreq > 0.0f);
    QVERIFY(Config::NoiseBaseFreq < 1.0f);

    // Test noise floor/ceil relationship
    QVERIFY(Config::NoiseFloor >= 0.0f);
    QVERIFY(Config::NoiseCeil > Config::NoiseFloor);
    QVERIFY(Config::NoiseCeil <= 1.0f);
}

void TestConfig::testBiomeLevels()
{
    // Test all biome levels are in valid range [0, 1]
    QVERIFY(Config::SeaLevel >= 0.0f && Config::SeaLevel <= 1.0f);
    QVERIFY(Config::BeachEnd >= 0.0f && Config::BeachEnd <= 1.0f);
    QVERIFY(Config::PlainsEnd >= 0.0f && Config::PlainsEnd <= 1.0f);
    QVERIFY(Config::ForestEnd >= 0.0f && Config::ForestEnd <= 1.0f);
    QVERIFY(Config::MountainEnd >= 0.0f && Config::MountainEnd <= 1.0f);

    // Test biome levels are in ascending order
    QVERIFY(Config::BeachEnd > Config::SeaLevel);
    QVERIFY(Config::PlainsEnd > Config::BeachEnd);
    QVERIFY(Config::ForestEnd > Config::PlainsEnd);
    QVERIFY(Config::MountainEnd > Config::ForestEnd);
}

void TestConfig::testZoomParameters()
{
    // Test zoom scale limits
    QVERIFY(Config::MinZoomScale > 0.0);
    QVERIFY(Config::MaxZoomScale > 1.0);
    QVERIFY(Config::MinZoomScale < Config::MaxZoomScale);
    QVERIFY(Config::MaxZoomScale <= 100.0);

    // Test zoom factors
    QVERIFY(Config::ZoomInFactor > 1.0);
    QVERIFY(Config::ZoomOutFactor > 0.0);
    QVERIFY(Config::ZoomOutFactor < 1.0);
    QVERIFY(Config::ZoomInFactor <= 2.0);  // Reasonable upper limit
    QVERIFY(Config::ZoomOutFactor >= 0.5); // Reasonable lower limit
}

void TestConfig::testBlurParameters()
{
    // Test blur radius
    QVERIFY(Config::BlurRadius >= 0);
    QVERIFY(Config::BlurRadius <= 10);

    // Test blur sigma divisor
    QVERIFY(Config::BlurSigmaDivisor > 0.0f);
    QVERIFY(Config::BlurSigmaDivisor <= 10.0f);
}

void TestConfig::testWindowParameters()
{
    // Test window dimensions are reasonable for displays
    QVERIFY(Config::WindowWidth >= 640);   // Minimum usable width
    QVERIFY(Config::WindowHeight >= 480);  // Minimum usable height
    QVERIFY(Config::WindowWidth <= 3840);  // 4K width limit
    QVERIFY(Config::WindowHeight <= 2160); // 4K height limit
}
