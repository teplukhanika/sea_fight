#include "PlayerProfile.h"

PlayerProfile::PlayerProfile(const string& playerName) {
    name = playerName;
    coins = 10;
    wins = 0;
    losses = 0;
}

string PlayerProfile::getName() const { return name; }
int PlayerProfile::getBalance() const { return coins; }

void PlayerProfile::recordWin() {
    wins++;
    coins += 5;
    cout << "[Система] Гравець " << name << " здобув перемогу! Нараховано 5 монет." << endl;
}

void PlayerProfile::recordLoss() {
    losses++;
    cout << "[Система] Гравець " << name << " зазнав поразки." << endl;
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
    cout << "\n=== ПРОФІЛЬ ГРАВЦЯ: " << name << " ===" << endl;
    cout << "Баланс: " << coins << " монет" << endl;
    cout << "Статистика: " << wins << " перемог / " << losses << " поразок" << endl;
    cout << "Інвентар:" << endl;
    if (inventory.empty()) {
        cout << "  - Інвентар порожній" << endl;
    }
    else {
        for (const auto& item : inventory) {
            cout << "  - " << item.first << ": " << item.second << " шт." << endl;
        }
    }
    cout << "=================================\n" << endl;
}