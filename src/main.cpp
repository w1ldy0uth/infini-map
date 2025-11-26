#include <QApplication>
#include "MapView.h"
#include "MapScene.h"

int main(int argc, char* argv[])
{
    QApplication app(argc, argv);

    MapScene* scene = new MapScene();
    MapView* view = new MapView();
    view->setScene(scene);

    view->setWindowTitle("InfiniMap");
    view->resize(1024, 768);
    view->show();

    return app.exec();
}
