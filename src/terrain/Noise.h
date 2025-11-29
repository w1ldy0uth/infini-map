#ifndef NOISE_H
#define NOISE_H

class Noise
{
public:
    static float normalizedValue2D(float x, float y, int seed = 0);

private:
    static float value2D(float x, float y, float frequency, int seed);
};

#endif
