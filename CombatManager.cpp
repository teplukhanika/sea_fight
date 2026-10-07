#include "CombatManager.h"
#include <iostream>

CombatManager::CombatManager(int startPlayer) : currentPlayer(startPlayer) {}

ShotResult CombatManager::processShot(FieldManager& field, int x, int y) {
    std::cout << "\nГравець " << currentPlayer << " робить постріл у (" << x << ", " << y << ")...\n";

    bool isHit = field.shoot(x, y);

    ShotResult res = isHit ? ShotResult::HIT : ShotResult::MISS;

    if (res == ShotResult::HIT) {
        std::cout << "Влучання! Гравець " << currentPlayer << " отримує додатковий хід.\n";
    }
    else {
        std::cout << "Промах. Хід переходить до іншого гравця.\n";
        switchTurn();
    }

    history.push_back(MoveRecord(x, y, res, currentPlayer));

    return res;
}

void CombatManager::volleyFire(FieldManager& field, const std::vector<std::pair<int, int>>& targets) {
    std::cout << "\nГравець " << currentPlayer << " викликає Авіаудар!\n";
    for (const auto& target : targets) {
        processShot(field, target.first, target.second);
    }
}

void CombatManager::switchTurn() {
    currentPlayer = (currentPlayer == 1) ? 2 : 1;
}

int CombatManager::getCurrentPlayer() const {
    return currentPlayer;
}

void CombatManager::printHistory() const {
    std::cout << "\nЖУРНАЛ БОЮ\n";
    for (const auto& record : history) {
        std::cout << record.toString() << "\n";
    }
}