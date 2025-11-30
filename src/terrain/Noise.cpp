#include "Noise.h"
#include <cmath>

// Fast 32-bit hash (Wang)
static unsigned int hash(unsigned int a)
{
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
    x *= frequency;
    y *= frequency;

    int x0 = (int)floorf(x);
    int y0 = (int)floorf(y);
    int x1 = x0 + 1;
    int y1 = y0 + 1;

    float sx = x - (float)x0;
    float sy = y - (float)y0;

    sx = fade(sx);
    sy = fade(sy);

    float n00 = unit((x0 << 16) + y0 + seed);
    float n10 = unit((x1 << 16) + y0 + seed);
    float n01 = unit((x0 << 16) + y1 + seed);
    float n11 = unit((x1 << 16) + y1 + seed);

    float ix0 = lerp(n00, n10, sx);
    float ix1 = lerp(n01, n11, sx);
    float iy = lerp(ix0, ix1, sy);

    return iy;
}

// Fractional Brownian motion (fBm)
float Noise::normalizedValue2D(float x, float y, int seed)
{
    float total = 0.0f;
    float maxAmplitude = 0.0f;
    float amplitude = 1.0f;
    float frequency = 0.002f;
    const int octaves = 5;

    for (int i = 0; i < octaves; ++i) {
        total += value2D(x, y, frequency, seed + i) * amplitude;
        maxAmplitude += amplitude;
        amplitude *= 0.6f;
        frequency *= 2.0f;
    }

    return total / maxAmplitude;
}
