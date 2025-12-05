#include "Noise.h"
#include "config/Config.h"
#include <cmath>

// Optimized 32-bit hash function
static unsigned int hash(unsigned int a)
{
    // Wang hash with minor optimizations
    a ^= 61;
    a ^= a >> 16;
    a += a << 3;
    a ^= a >> 4;
    a *= 0x27d4eb2d;
    a ^= a >> 15;
    return a;
}

// Hash to float in [0, 1]
static float unit(unsigned int n)
{
    return (hash(n) & 0x7fffffff) / 2147483647.0f;
}

// Linear interpolation
static float lerp(float a, float b, float t)
{
    return a + t * (b - a);
}

// Smooth interpolation
static float fade(float t)
{
    return t * t * (3.0f - 2.0f * t);
}

float Noise::value2D(float x, float y, float frequency, int seed)
{
    // Validate frequency parameter
    if (frequency <= 0.0f) {
        qWarning() << "Noise frequency must be positive:" << frequency;
        frequency = 0.001f; // Use reasonable default
    } else if (frequency > 100.0f) {
        qWarning() << "Noise frequency too high:" << frequency << "(may cause artifacts)";
    }

    // Scale coordinates
    x *= frequency;
    y *= frequency;

    // Get grid cell coordinates
    int x0 = (int)floorf(x);
    int y0 = (int)floorf(y);
    int x1 = x0 + 1;
    int y1 = y0 + 1;

    // Get fractional parts
    float sx = x - (float)x0;
    float sy = y - (float)y0;

    // Smooth the fractional parts
    sx = fade(sx);
    sy = fade(sy);

    // Generate noise values for the four corners
    // Use optimized hash combination
    float n00 = unit((x0 << 16) ^ (y0 + seed));
    float n10 = unit((x1 << 16) ^ (y0 + seed));
    float n01 = unit((x0 << 16) ^ (y1 + seed));
    float n11 = unit((x1 << 16) ^ (y1 + seed));

    // Bilinear interpolation
    float ix0 = lerp(n00, n10, sx);
    float ix1 = lerp(n01, n11, sx);
    float iy = lerp(ix0, ix1, sy);

    return iy;
}

// Fractional Brownian motion (fBm) with optimizations
float Noise::normalizedValue2D(float x, float y, int seed)
{
    // Basic input validation (coordinates can be any float values)
    // Seed validation: allow any int value as it's used in hash function

    float total = 0.0f;
    float maxAmplitude = 0.0f;
    float amplitude = 1.0f;
    float frequency = Config::NoiseBaseFreq;

    // Pre-calculate persistence and lacunarity powers for better performance
    for (int i = 0; i < Config::NoiseOctaves; ++i) {
        total += value2D(x, y, frequency, seed + i) * amplitude;
        maxAmplitude += amplitude;
        amplitude *= Config::NoisePersistence;
        frequency *= Config::NoiseLacunarity;
    }

    return total / maxAmplitude;
}
