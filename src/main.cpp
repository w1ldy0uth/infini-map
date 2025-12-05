#include <QApplication>
#include <QDebug>
#include <stdexcept>
#include "core/MapView.h"
#include "core/MapScene.h"
#include "config/Config.h"

int main(int argc, char* argv[])
{
    // Validate command line arguments
    if (argc > 1) {
        qWarning() << "InfiniMap doesn't accept command line arguments. Ignoring extra arguments.";
    }

    QApplication app(argc, argv);

    // Set application properties
    app.setApplicationName("InfiniMap");
    app.setApplicationVersion("0.1");
    app.setOrganizationName("InfiniMap");

    // Validate Qt initialization
    if (!QApplication::instance()) {
        qCritical() << "Failed to initialize Qt application";
        return 1;
    }

    try {
        MapScene scene;
        MapView view;

        // Validate scene creation
        if (!scene.sceneRect().isValid()) {
            qCritical() << "Failed to create valid scene";
            return 1;
        }

        view.setScene(&scene);

        if (!view.scene()) {
            qCritical() << "Failed to set scene on view";
            return 1;
        }

        view.setWindowTitle("InfiniMap");

        // Validate window dimensions
        if (Config::WindowWidth <= 0 || Config::WindowHeight <= 0) {
            qCritical() << "Invalid window dimensions:" << Config::WindowWidth << "x" << Config::WindowHeight;
            return 1;
        }

        view.resize(Config::WindowWidth, Config::WindowHeight);
        view.show();

        qInfo() << "InfiniMap started successfully";
        return app.exec();

    } catch (const std::exception& e) {
        qCritical() << "Application error:" << e.what();
        return 1;
    } catch (...) {
        qCritical() << "Unknown application error";
        return 1;
    }
}
