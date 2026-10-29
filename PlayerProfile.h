#pragma once
#include <iostream>
#include <string>
#include <map>
#include <iomanip>

using namespace std;

class FieldManager;

class PlayerProfile {
private:
    string name;
    string rankTitle;
    int coins;
    int wins;
    int losses;
    int totalDestroyedShips;
    map<string, int> inventory;

    void updateRank();

public:
    PlayerProfile(const string& playerName = "Гість");

    string getName() const;
    string getRank() const;
    int getBalance() const;
    int getWins() const;
    int getLosses() const;

    void addCoins(int amount);
    void addDestroyedShipKill();
    void recordWin();
    void recordLoss();
    bool spendCoins(int amount);

    void addItemToInventory(const string& itemName, int quantity = 1);
    bool hasItem(const string& itemName) const;

    bool useInventoryItem(const string& itemName, FieldManager& ownField,
        FieldManager& enemyField, int targetX, int targetY);

    void displayProfile() const;
};