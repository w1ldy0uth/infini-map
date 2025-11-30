#ifndef NOISE_H
#define NOISE_H
#pragma once

// 2D noise generator with fBm
class Noise
{
public:
    static float normalizedValue2D(float x, float y, int seed = 0);

private:
    static float value2D(float x, float y, float frequency, int seed);
};

#endif
