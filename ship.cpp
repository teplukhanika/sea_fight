#include "Ship.h"
#include <iostream>

using namespace std;

Ship::Ship(string shipName, int shipSize, MapLayer shipLayer) {
    name = shipName;
    size = shipSize;
    layer = shipLayer;
    startX = -1;
    startY = -1;
    isHorizontal = true;
    hits = 0;
    cout << "[Ship]: Створено корабель '" << name << "' (Розмір: " << size << ")\n";
}

Ship::~Ship() {
    cout << "[Ship]: Знищено корабель'" << name << "'\n";
}

string Ship::getName() const {
    return name;
}

int Ship::getSize() const {
    return size;
}
MapLayer Ship::getLayer() const { return layer; }
int Ship::getHits() const { return hits; }
int Ship::getStartX() const { return startX; }
int Ship::getStartY() const { return startY; }
bool Ship::getIsHorizontal() const { return isHorizontal; }

void Ship::setPosition(int x, int y, bool isHoriz) {
    startX = x;
    startY = y;
    isHorizontal = isHoriz;
}

bool Ship::occupies(int x, int y, MapLayer checkLayer) const {
    if (layer != checkLayer) return false;
    for (int i = 0; i < size; i++) {
        int cx = isHorizontal ? startX + i : startX;
        int cy = isHorizontal ? startY : startY + i;
        if (cx == x && cy == y) return true;
    }
    return false;
}

void Ship::hit() {
    if (hits < size) hits++;
}

bool Ship::isDestroyed() const {
    return hits >= size;
}

bool Ship::repairOneDeck() {
    if (hits > 0) {
        hits--;
        return true;
    }
    return false;
}

vector<pair<int, int>> Ship::getOccupiedCells() const {
    vector<pair<int, int>> cells;
    for (int i = 0; i < size; i++) {
        int cx = isHorizontal ? startX + i : startX;
        int cy = isHorizontal ? startY : startY + i;
        cells.push_back({ cx, cy });
    }
    return cells;
}