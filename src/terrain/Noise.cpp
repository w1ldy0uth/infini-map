#include "Noise.h"
#include <cmath>

static int hash(int n, int seed)
{
    n = (n ^ seed) * 1147297 + 1327217;
    n = (n ^ (n >> 14)) * 1327217;
    n = (n ^ (n >> 11)) * 16807;
    return n ^ (n >> 15);
}

float Noise::value2D(int x, int y, int seed)
{
    int fx = floor(x);
    int fy = floor(y);
    int h = hash(fx + fy * 57, seed);
    return (h % 65536) / 65535.0f;
}

float Noise::normalizedValue2D(int x, int y, int seed)
{
    float total = 0.0f;
    float maxAmplitude = 0.0f;
    float amplitude = 1.0f;
    float frequency = 0.01f;

    for (int i = 0; i < 4; ++i) {
        total += Noise::value2D(x * frequency, y * frequency, seed + i) * amplitude;
        maxAmplitude += amplitude;
        amplitude *= 0.5f;
        frequency *= 2.0f;
    }

    return total / maxAmplitude;
}
