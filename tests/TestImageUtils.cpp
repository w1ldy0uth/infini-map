#include "TestImageUtils.h"

void TestImageUtils::testGaussianBlur_validImage()
{
    // Create a test image
    const int width = 32;
    const int height = 32;
    QImage testImage(width, height, QImage::Format_RGB32);

    // Fill with a pattern
    testImage.fill(Qt::white);
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            if ((x + y) % 2 == 0) {
                testImage.setPixel(x, y, qRgb(255, 0, 0)); // Red
            } else {
                testImage.setPixel(x, y, qRgb(0, 255, 0)); // Green
            }
        }
    }

    // Apply blur
    QImage blurred = ImageUtils::gaussianBlur(testImage, 1);

    // Verify output
    QVERIFY(!blurred.isNull());
    QCOMPARE(blurred.width(), width);
    QCOMPARE(blurred.height(), height);
    QCOMPARE(blurred.format(), QImage::Format_RGB32);
}

void TestImageUtils::testGaussianBlur_nullImage()
{
    QImage nullImage;
    QImage result = ImageUtils::gaussianBlur(nullImage, 1);

    // Should return a null image for null input
    QVERIFY(result.isNull());
}

void TestImageUtils::testGaussianBlur_differentRadii()
{
    // Create a simple test image
    QImage testImage(16, 16, QImage::Format_RGB32);
    testImage.fill(Qt::white);
    // Add a black dot in the center
    testImage.setPixel(8, 8, qRgb(0, 0, 0));

    // Test different blur radii
    QImage blur1 = ImageUtils::gaussianBlur(testImage, 0); // No blur
    QImage blur2 = ImageUtils::gaussianBlur(testImage, 1); // Small blur
    QImage blur3 = ImageUtils::gaussianBlur(testImage, 2); // Larger blur

    // All should be valid
    QVERIFY(!blur1.isNull());
    QVERIFY(!blur2.isNull());
    QVERIFY(!blur3.isNull());

    QCOMPARE(blur1.size(), testImage.size());
    QCOMPARE(blur2.size(), testImage.size());
    QCOMPARE(blur3.size(), testImage.size());
}

void TestImageUtils::testGaussianBlur_edgeCases()
{
    // Test with very small image
    QImage tinyImage(1, 1, QImage::Format_RGB32);
    tinyImage.setPixel(0, 0, qRgb(128, 128, 128));

    QImage blurred = ImageUtils::gaussianBlur(tinyImage, 1);
    QVERIFY(!blurred.isNull());
    QCOMPARE(blurred.size(), QSize(1, 1));

    // Test with zero radius (should return original)
    QImage noBlur = ImageUtils::gaussianBlur(tinyImage, 0);
    QCOMPARE(noBlur.size(), tinyImage.size());
}

void TestImageUtils::testGaussianBlur_outputProperties()
{
    // Create test image with known properties
    const int width = 64;
    const int height = 48;
    QImage testImage(width, height, QImage::Format_RGB32);
    testImage.fill(qRgb(100, 150, 200));

    QImage blurred = ImageUtils::gaussianBlur(testImage, 2);

    QVERIFY(!blurred.isNull());
    QCOMPARE(blurred.width(), width);
    QCOMPARE(blurred.height(), height);
    QCOMPARE(blurred.format(), QImage::Format_RGB32);

    // Blurred image should be similar but not identical to original
    // (exact comparison depends on blur algorithm, but basic properties should hold)
    QVERIFY(blurred != testImage); // Should be different due to blurring

    // All pixels should be valid colors
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            QRgb pixel = blurred.pixel(x, y);
            QVERIFY(qRed(pixel) >= 0 && qRed(pixel) <= 255);
            QVERIFY(qGreen(pixel) >= 0 && qGreen(pixel) <= 255);
            QVERIFY(qBlue(pixel) >= 0 && qBlue(pixel) <= 255);
        }
    }
}
