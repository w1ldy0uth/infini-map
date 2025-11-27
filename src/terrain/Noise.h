#ifndef NOISE_H
#define NOISE_H
#pragma once

class Noise
{
public:
    static float value2D(int x, int y, int seed = 0);
    static float normalizedValue2D(int x, int y, int seed = 0);
};

#endif
