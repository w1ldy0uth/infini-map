#include "TestNoise.h"
#include "config/Config.h"
#include <cmath>

void TestNoise::testNormalizedValue2D_basic()
{
    // Test basic functionality
    float value = Noise::normalizedValue2D(0.0f, 0.0f, 12345);
    QVERIFY(std::isfinite(value));
    QVERIFY(value >= 0.0f && value <= 1.0f);
}

void TestNoise::testNormalizedValue2D_deterministic()
{
    // Test deterministic output with same inputs
    float value1 = Noise::normalizedValue2D(1.5f, 2.3f, 42);
    float value2 = Noise::normalizedValue2D(1.5f, 2.3f, 42);
    QCOMPARE(value1, value2);
}

void TestNoise::testNormalizedValue2D_range()
{
    // Test that output is always in [0, 1] range
    const int testPoints = 100;
    const int seed = 12345;

    for (int i = 0; i < testPoints; ++i) {
        float x = (i * 0.1f) - 5.0f; // Range from -5 to 5
        float y = (i * 0.07f) - 3.5f; // Range from -3.5 to 3.5

        float value = Noise::normalizedValue2D(x, y, seed);
        QVERIFY(value >= 0.0f && value <= 1.0f);
        QVERIFY(std::isfinite(value));
    }
}

void TestNoise::testNoiseContinuity()
{
    // Test that noise is reasonably continuous (small changes in input produce small changes in output)
    const int seed = 54321;
    const float baseX = 1.0f;
    const float baseY = 1.0f;
    const float epsilon = 0.01f;

    float centerValue = Noise::normalizedValue2D(baseX, baseY, seed);

    // Test points around the center
    float up = Noise::normalizedValue2D(baseX, baseY + epsilon, seed);
    float down = Noise::normalizedValue2D(baseX, baseY - epsilon, seed);
    float left = Noise::normalizedValue2D(baseX - epsilon, baseY, seed);
    float right = Noise::normalizedValue2D(baseX + epsilon, baseY, seed);

    // All neighboring values should be reasonably close to center (within 0.5)
    QVERIFY(qAbs(centerValue - up) < 0.5f);
    QVERIFY(qAbs(centerValue - down) < 0.5f);
    QVERIFY(qAbs(centerValue - left) < 0.5f);
    QVERIFY(qAbs(centerValue - right) < 0.5f);
}

void TestNoise::testNoiseProperties()
{
    // Test that noise has expected statistical properties
    const int samples = 1000;
    const int seed = 98765;

    double sum = 0.0;
    double sumSquares = 0.0;
    double minVal = 1.0;
    double maxVal = 0.0;

    for (int i = 0; i < samples; ++i) {
        float x = i * 0.01f;
        float y = i * 0.005f;
        float value = Noise::normalizedValue2D(x, y, seed);

        sum += value;
        sumSquares += value * value;
        minVal = qMin(minVal, (double)value);
        maxVal = qMax(maxVal, (double)value);
    }

    double mean = sum / samples;
    double variance = (sumSquares / samples) - (mean * mean);
    double stdDev = sqrt(variance);

    // Basic statistical checks
    QVERIFY(mean >= 0.4 && mean <= 0.6); // Should be roughly centered around 0.5
    QVERIFY(stdDev >= 0.1 && stdDev <= 0.3); // Should have reasonable spread
    QVERIFY(minVal >= 0.0 && minVal < 0.2); // Should reach near 0
    QVERIFY(maxVal > 0.8 && maxVal <= 1.0); // Should reach near 1
}
