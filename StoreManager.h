#pragma once

#include <string>
#include <vector>
#include "PlayerProfile.h"

using namespace std;

struct StoreItem {
    string name;
    int price;
    string description;
};

class StoreManager {
private:
    vector<StoreItem> catalog;

public:
    StoreManager();

    void displayCatalog() const;
    bool buyItem(PlayerProfile& player, const string& itemName);
};