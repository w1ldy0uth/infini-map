#pragma once

#include <QtTest/QtTest>
#include "config/Config.h"

class TestConfig : public QObject
{
    Q_OBJECT

private slots:
    void testMapDimensions();
    void testNoiseParameters();
    void testBiomeLevels();
    void testZoomParameters();
    void testBlurParameters();
    void testWindowParameters();
};
