#include "AttackAction.h"

string SingleShotAttack::getAttackName() const {
    return "Арт-постріл (Вода)";
}

int SingleShotAttack::execute(FieldManager& targetField, FieldManager* attackerField, int x, int y, Ship** outDestroyed) {
    return targetField.shoot(x, y, MapLayer::WATER, outDestroyed, attackerField);
}

string DepthChargeAttack::getAttackName() const {
    return "Глибинна бомба (Під водою)";
}

int DepthChargeAttack::execute(FieldManager& targetField, FieldManager* attackerField, int x, int y, Ship** outDestroyed) {
    return targetField.shoot(x, y, MapLayer::UNDERWATER, outDestroyed, attackerField);
}

string AntiAirAttack::getAttackName() const {
    return "Зенітка ППО (Повітря)";
}

int AntiAirAttack::execute(FieldManager& targetField, FieldManager* attackerField, int x, int y, Ship** outDestroyed) {
    return targetField.shoot(x, y, MapLayer::AIR, outDestroyed, attackerField);
}

string CrossVolleyAttack::getAttackName() const {
    return "Хрестовий залп (5 клітинок)";
}

int CrossVolleyAttack::execute(FieldManager& targetField, FieldManager* attackerField, int x, int y, Ship** outDestroyed) {
    int dirs[5][2] = { {0,0}, {1,0}, {-1,0}, {0,1}, {0,-1} };
    int bestStatus = 0;
    for (int i = 0; i < 5; i++) {
        Ship* temp = nullptr;
        int st = targetField.shoot(x + dirs[i][0], y + dirs[i][1], MapLayer::WATER, &temp, attackerField);
        if (st > bestStatus) bestStatus = st;
        if (temp != nullptr && outDestroyed != nullptr) *outDestroyed = temp;
    }
    return bestStatus;
}