#pragma once
#include "MapLayer.h"

class SeaMine {
private:
    int x;
    int y;
    MapLayer layer;
    bool triggered;

public:
    SeaMine(int posX, int posY, MapLayer mineLayer = MapLayer::WATER);
    ~SeaMine();

    int getX() const;
    int getY() const;
    MapLayer getLayer() const;
    bool isTriggered() const;
    void detonate();
};