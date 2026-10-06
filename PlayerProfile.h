#pragma once
#include <iostream>
#include <string>
#include <map>
#include <iomanip>

using namespace std;

class PlayerProfile {
private:
    string name;
    int coins;
    int wins;
    int losses;
    map<string, int> inventory;

public:
    PlayerProfile(const string& playerName);

    string getName() const;
    int getBalance() const;

    void recordWin();
    void recordLoss();
    bool spendCoins(int amount);
    void addItemToInventory(const string& itemName, int quantity = 1);
    void displayProfile() const;
};