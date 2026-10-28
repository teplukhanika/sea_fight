#pragma once
#include <vector>
#include "Ship.h"
#include "SeaMine.h"
#include "FleetPreset.h"

using namespace std;


class FieldManager {
private:
    static const int SIZE = 10;
    static const int LAYERS = 3;
    char grid[LAYERS][SIZE][SIZE];
    vector<Ship> ships;
    vector<SeaMine> mines;

public:
    FieldManager();
    ~FieldManager();

    void clearField();
    bool isInside(int x, int y) const;
    bool canPlace(int x, int y, int size, bool isHorizontal, MapLayer layer = MapLayer::WATER) const;
    bool placeShip(Ship ship, int x, int y, bool isHorizontal);
    void autoPlaceFleet(const FleetPreset& preset, int seedOffset = 0);
    bool placeMine(int x, int y, MapLayer layer = MapLayer::WATER);
    bool moveShip(size_t shipIndex, int dx, int dy);
    bool repairDamagedShip();
    int scanArea(int centerX, int centerY, MapLayer layer = MapLayer::WATER) const;

    // Повертає: 0 - промах, 1 - влучання, 2 - знищено, 3 - міна, -1 - помилка/повтор
    int shoot(int x, int y, MapLayer layer = MapLayer::WATER, Ship** outDestroyedShip = nullptr);
    void markCellAround(int x, int y, MapLayer layer = MapLayer::WATER);

    int getAliveShipsCount() const;
    bool areAllShipsDestroyed() const;

    void printField(MapLayer layer = MapLayer::WATER, bool fogOfWar = false) const;
    static void printSideBySide(const FieldManager& ownField, const FieldManager& enemyField, MapLayer layer = MapLayer::WATER);

};
