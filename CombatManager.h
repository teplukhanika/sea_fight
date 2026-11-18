#pragma once
#include <vector>
#include "MoveRecord.h"
#include "FieldManager.h"
#include "AttackAction.h"

using namespace std;

class CombatManager {
private:
    int turnCounter;
    vector<MoveRecord> history;

public:
    CombatManager();

    void autoSurroundDestroyedShip(FieldManager& field, const Ship& ship);
    ShotResult executeAttack(int playerId, AttackAction* attack, FieldManager& targetField, FieldManager* attackerField, int x, int y);
    void printFilteredHistory(bool onlySuccessfulHits) const;
};