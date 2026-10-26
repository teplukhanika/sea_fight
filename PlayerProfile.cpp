#include "PlayerProfile.h"

PlayerProfile::PlayerProfile(const string& playerName) {
    name = playerName;
    rankTitle = "Курсант";
    coins = 10;
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



void PlayerProfile::displayProfile() const {
    cout << "\n|^^^^ ПРОФІЛЬ ГРАВЦЯ: " << name << " [" << rankTitle << "] ^^^^|" << endl;
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
    cout << "|______________________________|\n" << endl;
}