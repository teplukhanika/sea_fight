#pragma once
#include <iostream>
#include <string>
#include <map>
#include <iomanip>

using namespace std;

class PlayerProfile {
private:
    string name;
    string rankTitle;
    int coins;
    int wins;
    int losses;
    int totalDestroyedShips;
    map<string, int> inventory;

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
    bool hasItem(const std::string& itemName) const;

    void displayProfile() const;
};