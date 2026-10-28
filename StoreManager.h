#pragma once

#include <string>
#include <vector>
#include "PlayerProfile.h"

using namespace std;

struct StoreItem {
    std::string name;
    int price;
    std::string description;
};

class StoreManager {
private:
    vector<StoreItem> catalog;

public:
    StoreManager();

    void displayCatalog() const;
    void buyItem(PlayerProfile& player, const string& itemName);
};