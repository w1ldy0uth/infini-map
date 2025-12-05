#pragma once

#include <QtTest/QtTest>
#include "terrain/BiomeColor.h"

class TestBiomeColor : public QObject
{
    Q_OBJECT

private slots:
    void testGetColor_validRange();
    void testGetColor_clamping();
    void testGetColor_biomeTransitions();
    void testGetColor_extremeValues();
};
