#pragma once

#include <QtTest/QtTest>
#include "utils/ImageUtils.h"

class TestImageUtils : public QObject
{
    Q_OBJECT

private slots:
    void testGaussianBlur_validImage();
    void testGaussianBlur_nullImage();
    void testGaussianBlur_differentRadii();
    void testGaussianBlur_edgeCases();
    void testGaussianBlur_outputProperties();
};
