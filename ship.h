#ifndef SHIP_H
#define SHIP_H

#include <string>
#include <vector>

enum class MapLayer {
    SURFACE = 0,
    UNDERWATER = 1
};

class Ship {
private:
    std::string name;
    int size;
    int startX;
    int startY;
    bool isHorizontal;
    MapLayer layer;
    int hits;

public:
    Ship(std::string shipName, int shipSize, MapLayer shipLayer = MapLayer::SURFACE);
    ~Ship();

    std::string getName() const;
    int getSize() const;
    MapLayer getLayer() const;
    int getHits() const;
    int getStartX() const;
    int getStartY() const;
    bool getIsHorizontal() const;

    void setPosition(int x, int y, bool isHoriz);
    bool occupies(int x, int y, MapLayer checkLayer) const;
    void hit();
    bool isDestroyed() const;
    bool repairOneDeck();

    std::vector<std::pair<int, int>> getOccupiedCells() const;
};

#endif 
