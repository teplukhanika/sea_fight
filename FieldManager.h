#ifndef FIELDMANAGER_H
#define FIELDMANAGER_H

#include "Ship.h"

class FieldManager {
private:
    static const int SIZE = 10;
    char grid[SIZE][SIZE];

public:
    FieldManager();
    ~FieldManager();

    void placeShip(const Ship& ship, int x, int y, bool isHorizontal);
    void printField() const;
    bool shoot(int x, int y);
    bool canPlace(int x, int y, int size, bool isHorizontal) const;
};

#endif 
