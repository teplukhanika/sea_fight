#include "Ship.h"
#include "FieldManager.h"
#include <iostream>

using namespace std;

Ship::Ship(string shipName, int shipSize, MapLayer shipLayer) {
    name = shipName;
    size = shipSize;
    hits = 0;
    startX = 0;
    startY = 0;
    isHorizontal = true;
    layer = shipLayer;
 
}
Ship::~Ship() {}
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


bool Ship::canMove() const { 
    return false;
}
void Ship::onTurnEnd(FieldManager& ownField) {}


Cruiser::Cruiser() : Ship("Крейсер", 3, MapLayer::WATER) {}
char Cruiser::getSymbol() const {
    return 'C'; 
}
Ship* Cruiser::clone() const {
    return new Cruiser(*this); 
}
void Cruiser::onDestroy(FieldManager& ownField, FieldManager* attackerField) const {
    cout << "  -> [Поліморфізм Cruiser]: Крейсер потопає, але здійснює прощальний залп у відповідь у ("
        << startX << ", " << startY << ")!\n";
    if (attackerField != nullptr) {
        attackerField->shoot(startX, startY, MapLayer::WATER);
    }
}

TankerShip::TankerShip() : Ship("Танкер", 2, MapLayer::WATER) {}
char TankerShip::getSymbol() const {
    return 'T'; 
}
Ship* TankerShip::clone() const {
    return new TankerShip(*this);
}
void TankerShip::onDestroy(FieldManager& ownField, FieldManager* attackerField) const {
    cout << "  -> [Поліморфізм TankerShip]: ДЕТОНАЦІЯ ПАЛЬНОГО! Танкер вибухає в радіусі 2 клітинки довкола себе!\n";
    vector<pair<int, int>> cells = getOccupiedCells();
    for (size_t i = 0; i < cells.size(); i++) {
        for (int dy = -2; dy <= 2; dy++) {
            for (int dx = -2; dx <= 2; dx++) {
                ownField.shoot(cells[i].first + dx, cells[i].second + dy, layer);
            }
        }
    }
}

Submarine::Submarine() : Ship("Субмарина", 2, MapLayer::UNDERWATER) {}
char Submarine::getSymbol() const {
    
    return 'U';
}
Ship* Submarine::clone() const {
    return new Submarine(*this);
}
void Submarine::onDestroy(FieldManager& ownField, FieldManager* attackerField) const {
    cout << "  -> [Поліморфізм Submarine]: Глибинна детонація! Субмарина затонула під водою.\n";
}

MovingBoat::MovingBoat() : Ship("Рухомий Катер", 1, MapLayer::WATER) {}
char MovingBoat::getSymbol() const {
    return 'B';
}
bool MovingBoat::canMove() const {
    return hits == 0;
}
Ship* MovingBoat::clone() const {
    return new MovingBoat(*this);
}
void MovingBoat::onTurnEnd(FieldManager& ownField) {
    if (canMove()) {
        ownField.tryShiftSingleCellShip(this, 1, 0);
    }
}
void MovingBoat::onDestroy(FieldManager& ownField, FieldManager* attackerField) const {
    cout << "  -> [Поліморфізм MovingBoat]: Швидкісний катер підірвано!\n";
}

AirDrone::AirDrone() : Ship("Авіадрон", 1, MapLayer::AIR) {}
char AirDrone::getSymbol() const {
    return 'D'; 
}
Ship* AirDrone::clone() const {
    return new AirDrone(*this); 
}
void AirDrone::onDestroy(FieldManager& ownField, FieldManager* attackerField) const {
    cout << "  -> [Поліморфізм AirDrone]: Дрон збито в повітрі!\n";
}
