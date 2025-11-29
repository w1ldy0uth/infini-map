#include <QApplication>
#include "core/MapView.h"
#include "core/MapScene.h"

int main(int argc, char* argv[])
{
    QApplication app(argc, argv);

    MapScene* scene = new MapScene();
    MapView* view = new MapView();
    view->setScene(scene);

    view->setWindowTitle("InfiniMap");
    view->resize(1600, 900);
    view->show();

    return app.exec();
}
