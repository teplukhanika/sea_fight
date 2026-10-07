#pragma once
#include "MoveRecord.h"
#include "FieldManager.h"

class CombatManager {
private:

    static const int MAX_HISTORY = 100;
    MoveRecord history[MAX_HISTORY];
    int historyCount;
    int currentPlayer;

public:
    CombatManager(int startPlayer = 1);

    ShotResult processShot(FieldManager& field, int x, int y);

    void volleyFire(FieldManager& field, const int targetX[], const int targetY[], int count);

    void switchTurn();
    int getCurrentPlayer() const;
    void printHistory() const;
};