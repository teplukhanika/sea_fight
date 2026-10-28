#include "Ship.h"
#include <iostream>

using namespace std;

Ship::Ship(string shipName, int shipSize, MapLayer shipLayer, bool tanker, bool counter) {
    name = shipName;
    size = shipSize;
    hits = 0;
    startX = 0;
    startY = 0;
    isHorizontal = true;
    layer = shipLayer;
    isTanker = tanker;
    canCounter = counter;

    cout << "[Ship]: Створено корабель '" << name << "' (Розмір: " << size << ")\n";
}
Ship::~Ship() {
    cout << "[Ship]: Знищено корабель'" << name << "'\n";
}
void Ship::setPosition(int x, int y, bool horiz) {
    startX = x;
    startY = y;
    isHorizontal = horiz;
}

string Ship::getName() const {
    return name;
}

int Ship::getSize() const {
    return size;
}

int Ship::getHits() const {
    return hits;
}

int Ship::getRemainingHP() const {
    return size - hits;
}

int Ship::getStartX() const {
    return startX;
}

int Ship::getStartY() const {
    return startY;
}

bool Ship::getIsHorizontal() const {
    return isHorizontal;
}

MapLayer Ship::getLayer() const {
    return layer;
}

bool Ship::getIsTanker() const {
    return isTanker;
}

bool Ship::getCanCounter() const {
    return canCounter;
}

void Ship::hit() {
    if (hits < size) {
        hits++;
    }
}

bool Ship::repairOneDeck() {
    if (hits > 0 && !isDestroyed()) {
        hits--;
        return true;
    }
    return false;
}

bool Ship::isDestroyed() const {
    return hits >= size;
}

vector<pair<int, int>> Ship::getOccupiedCells() const {
    vector<pair<int, int>> cells;
    for (int i = 0; i < size; i++) {
        int cx = startX;
        int cy = startY;

        if (isHorizontal) {
            cx = startX + i;
        }
        else {
            cy = startY + i;
        }

        cells.push_back({ cx, cy });
    }
    return cells;
}

bool Ship::occupies(int x, int y, MapLayer targetLayer) const {
    if (layer != targetLayer) {
        return false;
    }

    vector<pair<int, int>> cells = getOccupiedCells();
    for (size_t i = 0; i < cells.size(); i++) {
        if (cells[i].first == x && cells[i].second == y) {
            return true;
        }
    }
    return false;
}