#include "CombatManager.h"
#include <iostream>

using namespace std;

CombatManager::CombatManager(int startPlayer)
    : currentPlayer(startPlayer), historyCount(0) {
}

ShotResult CombatManager::processShot(FieldManager& field, int x, int y) {
    cout << "\n Гравець " << currentPlayer << " робить постріл у (" << x << ", " << y << ")...\n";


    bool isHit = field.shoot(x, y);

    ShotResult res = isHit ? ShotResult::HIT : ShotResult::MISS;

    if (res == ShotResult::HIT) {
        cout << " Влучання! Гравець " << currentPlayer << " отримує додатковий хід.\n";
    }
    else {
        cout << "Промах. Хід переходить до іншого гравця.\n";
        switchTurn();
    }


    if (historyCount < MAX_HISTORY) {
        history[historyCount] = MoveRecord(x, y, res, currentPlayer);
        historyCount++;
    }

    return res;
}

void CombatManager::volleyFire(FieldManager& field, const int targetX[], const int targetY[], int count) {
    cout << "\n Гравець " << currentPlayer << " викликає Авіаудар!\n";
    for (int i = 0; i < count; ++i) {
        processShot(field, targetX[i], targetY[i]);
    }
}

void CombatManager::switchTurn() {
    currentPlayer = (currentPlayer == 1) ? 2 : 1;
}

int CombatManager::getCurrentPlayer() const {
    return currentPlayer;
}

void CombatManager::printHistory() const {
    cout << "ЖУРНАЛ БОЮ\n";
    for (int i = 0; i < historyCount; ++i) {
        cout << history[i].toString() << "\n";
    }
}