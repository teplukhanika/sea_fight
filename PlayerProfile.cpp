#include "PlayerProfile.h"
#include "FieldManager.h"

PlayerProfile::PlayerProfile(const string& playerName) {
    name = playerName;
    rankTitle = "Курсант";
    coins = 15;
    wins = 0;
    losses = 0;
    totalDestroyedShips = 0;
}

string PlayerProfile::getName() const { return name; }
string PlayerProfile::getRank() const { return rankTitle; }
int PlayerProfile::getBalance() const { return coins; }
int PlayerProfile::getWins() const { return wins; }
int PlayerProfile::getLosses() const { return losses; }

void PlayerProfile::updateRank() {
    if (wins >= 5) rankTitle = "Адмірал флоту";
    else if (wins >= 2) rankTitle = "Капітан І рангу";
    else if (wins >= 1) rankTitle = "Лейтенант";
    else rankTitle = "Курсант";
}

void PlayerProfile::recordWin() {
    wins++;
    coins += 10;
    updateRank();
    cout << "[Система] Гравець " << name << " здобув перемогу! Нараховано 10 монет. Ваше звання: " << rankTitle << endl;
}

void PlayerProfile::recordLoss() {
    losses++;
    coins += 2;
    cout << "[Система] Гравець " << name << " зазнав поразки. Нараховано +2 монети, як втішний бонус." << endl;
}

void PlayerProfile::addDestroyedShipKill() {
    totalDestroyedShips++;
    coins += 2;
}

void PlayerProfile::addCoins(int amount) {
    if (amount > 0) coins += amount;
}

bool PlayerProfile::spendCoins(int amount) {
    if (amount < 0) return false;
    if (coins >= amount) {
        coins -= amount;
        return true;
    }
    return false;
}

void PlayerProfile::addItemToInventory(const string& itemName, int quantity) {
    inventory[itemName] += quantity;
}

bool PlayerProfile::hasItem(const string& itemName) const {
    auto it = inventory.find(itemName);
    return it != inventory.end() && it->second > 0;
}

bool PlayerProfile::useInventoryItem(const string& itemName, FieldManager& ownField,
    FieldManager& enemyField, int targetX, int targetY) {
    if (!hasItem(itemName)) {
        cout << "[Інвентар]: У гравця " << name << " немає предмета '" << itemName << "'!\n";
        return false;
    }

    inventory[itemName]--;
    if (inventory[itemName] == 0) inventory.erase(itemName);

    cout << "[Інвентар]: Гравець " << name << " активує спецзасіб '" << itemName << "'!\n";
    if (itemName == "Радар") {
        int found = enemyField.scanArea(targetX, targetY, MapLayer::WATER);
        cout << "  -> [Радар]: У радіусі 3x3 навколо (" << targetX << "," << targetY
            << ") виявлено об'єктів противника: " << found << " шт.\n";
    }
    else if (itemName == "Міна") {
        ownField.placeMine(targetX, targetY, MapLayer::WATER);
    }
    else if (itemName == "Ремкомплект") {
        ownField.repairDamagedShip();
    }
    else if (itemName == "Авіаудар") {
        for (int dx = 0; dx < 3; dx++) {
            enemyField.shoot(targetX + dx, targetY, MapLayer::WATER);
        }
    }
    return true;
}

void PlayerProfile::displayProfile() const {
    cout << "\n|^^^^^^^^^^^^^^^^ ПРОФІЛЬ ГРАВЦЯ: " << name << " [" << rankTitle << "] ^^^^^^^^^^^^^^^^|" << endl;
    cout << "Баланс: " << coins << " монет" << endl;
    cout << "Статистика: " << wins << " перемог / " << losses << " поразок" << " | Потоплено кораблів: " << totalDestroyedShips << endl;
    cout << "Інвентар:" << endl;
    if (inventory.empty()) {
        cout << "  - Інвентар порожній" << endl;
    }
    else {
        for (const auto& item : inventory) {
            cout << "  - " << item.first << ": " << item.second << " шт." << endl;
        }
    }
    cout << "|_________________________________________________________________|\n" << endl;
}