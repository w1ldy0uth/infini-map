#include "Noise.h"
#include <cmath>

static unsigned int hash(unsigned int a)
{
    a = (a ^ 61) ^ (a >> 16);
    a = a + (a << 3);
    a = a ^ (a >> 4);
    a = a * 0x27d4eb2d;
    a = a ^ (a >> 15);
    return a;
}

// Random float [0,1] from integer hash
static float randFloat(unsigned int n)
{
    return (hash(n) & 0x7fffffff) / 2147483647.0f;
}

// Smoothstep interpolation
static float lerp(float a, float b, float t)
{
    return a + t * (b - a);
}

static float smooth(float t)
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

    sx = smooth(sx);
    sy = smooth(sy);

    unsigned int hash00 = hash((x0 << 16) + y0) + seed;
    unsigned int hash10 = hash((x1 << 16) + y0) + seed;
    unsigned int hash01 = hash((x0 << 16) + y1) + seed;
    unsigned int hash11 = hash((x1 << 16) + y1) + seed;

    float n00 = randFloat(hash00);
    float n10 = randFloat(hash10);
    float n01 = randFloat(hash01);
    float n11 = randFloat(hash11);

    float ix0 = lerp(n00, n10, sx);
    float ix1 = lerp(n01, n11, sx);
    float iy = lerp(ix0, ix1, sy);

    return iy;
}

// fBm
float Noise::normalizedValue2D(float x, float y, int seed)
{
    float total = 0.0f;
    float maxAmplitude = 0.0f;
    float amplitude = 1.0f;
    float frequency = 0.002f;
    int octaves = 5;

    for (int i = 0; i < octaves; ++i) {
        total += value2D(x, y, frequency, seed + i) * amplitude;
        maxAmplitude += amplitude;
        amplitude *= 0.6f;
        frequency *= 2.0f;
    }

    return total / maxAmplitude;
}
