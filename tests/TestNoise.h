#pragma once

#include <QtTest/QtTest>
#include "terrain/Noise.h"

class TestNoise : public QObject
{
    Q_OBJECT

private slots:
    void testNormalizedValue2D_basic();
    void testNormalizedValue2D_deterministic();
    void testNormalizedValue2D_range();
    void testNoiseContinuity();
    void testNoiseProperties();
};
