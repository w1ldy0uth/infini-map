#include <QtTest/QtTest>
#include <QApplication>

// Test includes
#include "TestNoise.h"
#include "TestBiomeColor.h"
#include "TestImageUtils.h"
#include "TestConfig.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    // Set application properties for testing
    app.setApplicationName("InfiniMapTests");
    app.setApplicationVersion("1.0");

    int status = 0;

    // Run all test suites
    {
        TestNoise testNoise;
        status |= QTest::qExec(&testNoise, argc, argv);
    }

    {
        TestBiomeColor testBiomeColor;
        status |= QTest::qExec(&testBiomeColor, argc, argv);
    }

    {
        TestImageUtils testImageUtils;
        status |= QTest::qExec(&testImageUtils, argc, argv);
    }

    {
        TestConfig testConfig;
        status |= QTest::qExec(&testConfig, argc, argv);
    }

    return status;
}
