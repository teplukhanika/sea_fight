#include "SeaMine.h"
#include <iostream>
using namespace std;

SeaMine::SeaMine(int posX, int posY, MapLayer mineLayer) {
    x = posX;
    y = posY;
    layer = mineLayer;
    triggered = false;
}

SeaMine::~SeaMine() {}

int SeaMine::getX() const {
    return x;
}

int SeaMine::getY() const {
    return y;
}

MapLayer SeaMine::getLayer() const {
    return layer;
}

bool SeaMine::isTriggered() const {
    return triggered;
}

void SeaMine::detonate() {
    triggered = true;
}