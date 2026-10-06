#pragma once

#include <string>
#include <map>
#include "PlayerProfile.h"

using namespace std;

class StoreManager {
private:
    std::map<string, int> catalog;

public:
    StoreManager();

    void displayCatalog() const;
    void buyItem(PlayerProfile& player, const string& itemName);
};