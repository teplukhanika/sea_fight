#include "CombatManager.h"
#include <iostream>

CombatManager::CombatManager() : turnCounter(1) {}

void CombatManager::autoSurroundDestroyedShip(FieldManager& field, const Ship& ship) {
    vector<pair<int, int>> cells = ship.getOccupiedCells();
    for (size_t i = 0; i < cells.size(); i++) {
        for (int dy = -1; dy <= 1; dy++) {
            for (int dx = -1; dx <= 1; dx++) {
                field.markCellAround(cells[i].first + dx, cells[i].second + dy, ship.getLayer());
            }
        }
    }
}

ShotResult CombatManager::executeAttack(int playerId, AttackAction* attack, FieldManager& targetField, FieldManager* attackerField, int x, int y) {
    cout << "\n[CombatManager]: Гравець " << playerId << " застосовує '" << attack->getAttackName()
        << "' у (" << x << "," << y << ")...\n";
    Ship* destroyedShip = nullptr;
    int status = attack->execute(targetField, attackerField, x, y, &destroyedShip);

    ShotResult res = (status == 3) ? ShotResult::MINE_TRIGGERED :
        (status == 2) ? ShotResult::DESTROYED :
        (status == 1) ? ShotResult::HIT : ShotResult::MISS;

    history.push_back(MoveRecord(turnCounter++, playerId, x, y, attack->getAttackName(), res));

    if (res == ShotResult::DESTROYED && destroyedShip != nullptr) {
        autoSurroundDestroyedShip(targetField, *destroyedShip);
    }
    return res;
}

void CombatManager::printFilteredHistory(bool onlySuccessfulHits) const {
    cout << "\n=== ЖУРНАЛ БОЮ (" << (onlySuccessfulHits ? "Тільки влучання/знищення" : "Усі ходи") << ") ===\n";
    for (size_t i = 0; i < history.size(); i++) {
        if (!onlySuccessfulHits || history[i].getResult() == ShotResult::HIT || history[i].getResult() == ShotResult::DESTROYED) {
            cout << "  " << history[i].toString() << "\n";
        }
    }
}