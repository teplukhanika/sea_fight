#pragma once
#include "MoveRecord.h"
#include "FieldManager.h"
#include <vector>
#include <utility>

class CombatManager {
private:
    std::vector<MoveRecord> history;
    int currentPlayer;

public:
    CombatManager(int startPlayer = 1);

    ShotResult processShot(FieldManager& field, int x, int y);
    void volleyFire(FieldManager& field, const std::vector<std::pair<int, int>>& targets);

    void switchTurn();
    int getCurrentPlayer() const;
    void printHistory() const;
};