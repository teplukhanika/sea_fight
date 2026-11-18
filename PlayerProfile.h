#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <iomanip>
#include "ShopItem.h"

using namespace std;

class FieldManager;

class PlayerProfile {
private:
    string name;
    int coins;
    int wins;
    int losses;
    std::vector<ShopItem*> inventory;


public:
    PlayerProfile(const string& playerName = "Гість", int startCoins = 20, int w = 0, int l = 0);
    PlayerProfile(const PlayerProfile& other);
    PlayerProfile& operator=(const PlayerProfile& other);
    ~PlayerProfile();

    string getName() const;
    int getBalance() const;
    int getWins() const;
    int getLosses() const;

    void recordWin();
    void recordLoss();
    bool spendCoins(int amount);

    void addItem(ShopItem* item);
    bool useItem(const std::string& itemName, FieldManager& ownField, FieldManager& enemyField, int x, int y);

    string serialize() const;
    static bool deserialize(const std::string& line, PlayerProfile& out);
    void display() const;
};