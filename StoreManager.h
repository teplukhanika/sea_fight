#pragma once

#include <string>
#include <vector>
#include "ShopItem.h"
#include "PlayerProfile.h"

using namespace std;

class StoreManager {
private:
    vector<ShopItem*> catalog;

public:
    StoreManager();
    ~StoreManager();
    
    void buyItem(PlayerProfile& player, const string& itemName);
};