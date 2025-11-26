#ifndef MAPSCENE_H
#define MAPSCENE_H

#include <QGraphicsScene>

class MapScene : public QGraphicsScene
{
    Q_OBJECT

public:
    MapScene(QObject* parent = nullptr);
    void paintTerrain();

private:
    int width  = 2048;
    int height = 2048;
};

#endif
