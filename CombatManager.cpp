#include "CombatManager.h"
#include <iostream>
#include <iomanip>

CombatManager::CombatManager(FieldManager* f1, FieldManager* f2)
    : currentPlayer(1), totalTurns(1), fieldP1(f1), fieldP2(f2) {
}

void CombatManager::bindFields(FieldManager* f1, FieldManager* f2) {
    fieldP1 = f1;
    fieldP2 = f2;
}

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

void CombatManager::triggerTankerExplosion(FieldManager& field, const Ship& tanker) {
    cout << "  Спецефект Танкера: Детонація пального обстрілює радіус 2 клітинки довкола\n";
    vector<pair<int, int>> cells = tanker.getOccupiedCells();
    for (size_t i = 0; i < cells.size(); i++) {
        for (int dy = -2; dy <= 2; dy++) {
            for (int dx = -2; dx <= 2; dx++) {
                field.shoot(cells[i].first + dx, cells[i].second + dy, tanker.getLayer());
            }
        }
    }
}

ShotResult CombatManager::processShot(FieldManager& targetField, int x, int y, MapLayer layer) {
    Ship* destroyedShip = nullptr;
    int status = targetField.shoot(x, y, layer, &destroyedShip);

    ShotResult res = ShotResult::INVALID;
    string shipName = "";

    if (status == 0) res = ShotResult::MISS;
    else if (status == 1) res = ShotResult::HIT;
    else if (status == 2) {
        res = ShotResult::DESTROYED;
        if (destroyedShip) shipName = destroyedShip->getName();
    }
    else if (status == 3) {
        res = ShotResult::MINE_TRIGGERED;
    }

    history.push_back(MoveRecord(totalTurns++, currentPlayer, x, y, layer, res, shipName));

    if (res == ShotResult::DESTROYED && destroyedShip != nullptr) {
        cout << "Бій: Гравець " << currentPlayer << " Знищив корабель '" << shipName << "' у (" << x << "," << y << ")\n";
        autoSurroundDestroyedShip(targetField, *destroyedShip);
        if (destroyedShip->getIsTanker()) {
            triggerTankerExplosion(targetField, *destroyedShip);
        }
        if (destroyedShip->getCanCounter() && fieldP1 && fieldP2) {
            cout << "  Спецефект Крейсера: Корабель дає прощальний залп у відповідь по полю атакуючого\n";
            FieldManager* attackerField = (currentPlayer == 1) ? fieldP1 : fieldP2;
            attackerField->shoot(x, y, MapLayer::WATER);
        }
    }
    else if (res == ShotResult::HIT) {
        cout << "Бій: Гравець " << currentPlayer << " влучив у (" << x << "," << y << ") Додатковий хід\n";
    }
    else if (res == ShotResult::MINE_TRIGGERED) {
        cout << "Бій: Гравець " << currentPlayer << " натрапив на міну, Хід переходить далі\n";
        switchTurn();
    }
    else if (res == ShotResult::MISS) {
        cout << "Бій: Гравець " << currentPlayer << " промахнувся у (" << x << "," << y << "). Перехід ходу\n";
        switchTurn();
    }

    return res;
}

void CombatManager::volleyFire(FieldManager& targetField, const vector<pair<int, int>>& targets, MapLayer layer) {
    cout << "Бій: Гравець " << currentPlayer << " виконує залповий Авіаудар по " << targets.size() << " цілях\n";
    for (size_t i = 0; i < targets.size(); i++) {
        processShot(targetField, targets[i].first, targets[i].second, layer);
    }
}

void CombatManager::switchTurn() {
    currentPlayer = (currentPlayer == 1) ? 2 : 1;
}

int CombatManager::getCurrentPlayer() const { return currentPlayer; }

double CombatManager::getPlayerAccuracy(int playerId) const {
    int shots = 0, hits = 0;
    for (size_t i = 0; i < history.size(); i++) {
        if (history[i].getPlayerId() == playerId) {
            shots++;
            if (history[i].getResult() == ShotResult::HIT || history[i].getResult() == ShotResult::DESTROYED) {
                hits++;
            }
        }
    }
    return (shots == 0) ? 0.0 : (100.0 * hits / shots);
}

void CombatManager::printHistory() const {
    cout << "\nЖурнал бою (" << history.size() << " записів)\n";
    for (size_t i = 0; i < history.size(); i++) {
        cout << "  " << history[i].toString() << "\n";
    }
    cout << "Точність Гравця 1: " << fixed << setprecision(1) << getPlayerAccuracy(1) << "% | "
        << "Точність Гравця 2: " << getPlayerAccuracy(2) << "%\n";
}