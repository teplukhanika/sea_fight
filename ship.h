#pragma once
#include <string>
#include <vector>
#include <utility>
#include "MapLayer.h"

using namespace std;

class FieldManager;

class Ship {
protected:
    string name;
    int size;
    int hits;
    int startX;
    int startY;
    bool isHorizontal;
    MapLayer layer;

public:
    Ship(string shipName, int shipSize, MapLayer shipLayer = MapLayer::WATER);
    virtual ~Ship();

    void setPosition(int x, int y, bool horiz);

    string getName() const;
    int getSize() const;
    int getHits() const;
    int getRemainingHP() const;
    int getStartX() const;
    int getStartY() const;
    bool getIsHorizontal() const;
    MapLayer getLayer() const;
  

    void hit();
    bool repairOneDeck();
    bool isDestroyed() const;

    vector<pair<int, int>> getOccupiedCells() const;
    bool occupies(int x, int y, MapLayer targetLayer) const;

    virtual char getSymbol() const = 0; 
    virtual bool canMove() const;   
    virtual void onTurnEnd(FieldManager& ownField); 
    virtual void onDestroy(FieldManager& ownField, FieldManager* attackerField) const = 0; 
    virtual Ship* clone() const = 0;   
};

class Cruiser : public Ship {
public:
    Cruiser();
    char getSymbol() const override;
    void onDestroy(FieldManager& ownField, FieldManager* attackerField) const override;
    Ship* clone() const override;
};

class TankerShip : public Ship {
public:
    TankerShip();
    char getSymbol() const override;
    void onDestroy(FieldManager& ownField, FieldManager* attackerField) const override;
    Ship* clone() const override;
};

class Submarine : public Ship {
public:
    Submarine();
    char getSymbol() const override;
    void onDestroy(FieldManager& ownField, FieldManager* attackerField) const override;
    Ship* clone() const override;
};

class MovingBoat : public Ship {
public:
    MovingBoat();
    char getSymbol() const override;
    bool canMove() const override;
    void onTurnEnd(FieldManager& ownField) override;
    void onDestroy(FieldManager& ownField, FieldManager* attackerField) const override;
    Ship* clone() const override;
};

class AirDrone : public Ship {
public:
    AirDrone();
    char getSymbol() const override;
    void onDestroy(FieldManager& ownField, FieldManager* attackerField) const override;
    Ship* clone() const override;
};
