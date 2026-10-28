#pragma once
#include <vector>
#include "MoveRecord.h"
#include "FieldManager.h"

using namespace std;

class CombatManager {
private:
    int currentPlayer;
    int totalTurns;
    vector<MoveRecord> history;
    FieldManager* fieldP1;
    FieldManager* fieldP2;

public:
    CombatManager(FieldManager* f1 = nullptr, FieldManager* f2 = nullptr);
    void bindFields(FieldManager* f1, FieldManager* f2);

    void autoSurroundDestroyedShip(FieldManager& field, const Ship& ship);
    void triggerTankerExplosion(FieldManager& field, const Ship& tanker);

    ShotResult processShot(FieldManager& targetField, int x, int y, MapLayer layer = MapLayer::WATER);
    void volleyFire(FieldManager& targetField, const vector<pair<int, int>>& targets, MapLayer layer = MapLayer::WATER);

    void switchTurn();
    int getCurrentPlayer() const;
    double getPlayerAccuracy(int playerId) const;
    void printHistory() const;
};