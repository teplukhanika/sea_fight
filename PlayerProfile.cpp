#include "PlayerProfile.h"
#include "FieldManager.h"
#include <iostream>
#include <iomanip>
#include <sstream>

using namespace std;

PlayerProfile::PlayerProfile(const string& playerName, int startCoins, int w, int l)
    : name(playerName), coins(startCoins), wins(w), losses(l) {
}

PlayerProfile::PlayerProfile(const PlayerProfile& other)
    : name(other.name), coins(other.coins), wins(other.wins), losses(other.losses) {
    for (size_t i = 0; i < other.inventory.size(); i++) {
        inventory.push_back(other.inventory[i]->clone());
    }
}

PlayerProfile& PlayerProfile::operator=(const PlayerProfile& other) {
    if (this != &other) {
        for (size_t i = 0; i < inventory.size(); i++) delete inventory[i];
        inventory.clear();
        name = other.name;
        coins = other.coins;
        wins = other.wins;
        losses = other.losses;
        for (size_t i = 0; i < other.inventory.size(); i++) {
            inventory.push_back(other.inventory[i]->clone());
        }
    }
    return *this;
}

PlayerProfile::~PlayerProfile() {
    for (size_t i = 0; i < inventory.size(); i++) delete inventory[i];
}

string PlayerProfile::getName() const { return name; }
int PlayerProfile::getBalance() const { return coins; }
int PlayerProfile::getWins() const { return wins; }
int PlayerProfile::getLosses() const { return losses; }



void PlayerProfile::recordWin() { wins++; coins += 10; }
void PlayerProfile::recordLoss() { losses++; coins += 2; }

bool PlayerProfile::spendCoins(int amount) {
    if (amount < 0) return false;
    if (coins >= amount) {
        coins -= amount;
        return true;
    }
    return false;
}

void PlayerProfile::addItem(ShopItem* item) { inventory.push_back(item); }

bool PlayerProfile::useItem(const string& itemName, FieldManager& ownField, FieldManager& enemyField, int x, int y) {
    for (size_t i = 0; i < inventory.size(); i++) {
        if (inventory[i]->getName() == itemName) {
            inventory[i]->applyEffect(ownField, enemyField, x, y);
            delete inventory[i];
            inventory.erase(inventory.begin() + i);
            return true;
        }
    }
    return false;
}

string PlayerProfile::serialize() const {
    string items;
    for (size_t i = 0; i < inventory.size(); i++) {
        if (i > 0) items += ",";
        items += inventory[i]->getName();
    }
    return name + ";" + to_string(coins) + ";" + to_string(wins) + ";" +
        to_string(losses) + ";" + items;
}

bool PlayerProfile::deserialize(const string& line, PlayerProfile& out) {
    vector<string> parts;
    stringstream ss(line);
    string token;
    while (getline(ss, token, ';')) parts.push_back(token);
    if (!line.empty() && line.back() == ';') parts.push_back("");
    if (parts.size() < 4 || parts[0].empty()) return false;

    int c, w, l;
    try {
        c = stoi(parts[1]);
        w = stoi(parts[2]);
        l = stoi(parts[3]);
    }
    catch (...) {
        return false;
    }

    PlayerProfile result(parts[0], c, w, l);
    if (parts.size() >= 5 && !parts[4].empty()) {
        stringstream is(parts[4]);
        string itemName;
        while (getline(is, itemName, ',')) {
            ShopItem* item = createShopItem(itemName);
            if (item) result.addItem(item);
        }
    }
    out = result;
    return true;
}

void PlayerProfile::display() const {
    cout << "  Гравець: " << left << setw(14) << name << " | Монет: " << setw(3) << coins
        << " | Перемог: " << wins << " | Поразок: " << losses
        << " | Предметів: " << inventory.size() << "\n";
}