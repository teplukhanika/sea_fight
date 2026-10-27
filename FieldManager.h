#ifndef FIELDMANAGER_H
#define FIELDMANAGER_H

#include "Ship.h"
#include <vector>
const int SIZE = 10;
const int LAYERS = 2;


class FieldManager {
private:
    char grid[LAYERS][SIZE][SIZE];
    std::vector<Ship> ships;

    void clearField();
    bool isInside(int x, int y) const;
    bool canPlace(int x, int y, int size, bool isHorizontal, MapLayer layer) const;

public:
    FieldManager();
    ~FieldManager();

    bool placeShip(Ship ship, int x, int y, bool isHorizontal);
    void printField(MapLayer layer, bool fogOfWar = false) const;
    int shoot(int x, int y, MapLayer layer, Ship** outDestroyedShip = nullptr);
    bool canPlace(int x, int y, int size, bool isHorizontal) const;
    bool placeMine(int x, int y, MapLayer layer);
    bool moveShip(size_t shipIndex, int dx, int dy);
    bool repairDamagedShip();
    int scanArea(int centerX, int centerY, MapLayer layer) const;

    void markCellAround(int x, int y, MapLayer layer);
    int getAliveShipsCount() const;
    bool areAllShipsDestroyed() const;

    static void printSideBySide(const FieldManager& ownField, const FieldManager& enemyField, MapLayer layer);
};

#endif 
