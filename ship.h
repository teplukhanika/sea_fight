#pragma once
#include <string>
#include <vector>
#include <utility>
#include "MapLayer.h"

using namespace std;

class Ship {
private:
    std::string name;
    int size;
    int hits;
    int startX;
    int startY;
    bool isHorizontal;
    MapLayer layer;
    bool isTanker;
    bool canCounter;

public:
    Ship(string shipName, int shipSize, MapLayer shipLayer = MapLayer::WATER, bool tanker = false, bool counter = false);
    ~Ship();

    void setPosition(int x, int y, bool horiz);

    string getName() const;
    int getSize() const;
    int getHits() const;
    int getRemainingHP() const;
    int getStartX() const;
    int getStartY() const;
    bool getIsHorizontal() const;
    MapLayer getLayer() const;
    bool getIsTanker() const;
    bool getCanCounter() const;

    void hit();
    bool repairOneDeck();
    bool isDestroyed() const;

    vector<pair<int, int>> getOccupiedCells() const;
    bool occupies(int x, int y, MapLayer targetLayer) const;
};
