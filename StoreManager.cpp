#include "StoreManager.h"

#include <iostream>

StoreManager::StoreManager() {
    catalog.push_back(new SeaMineItem());
    catalog.push_back(new RadarItem());
    catalog.push_back(new RepairKitItem());
}

StoreManager::~StoreManager() {
    for (size_t i = 0; i < catalog.size(); i++) delete catalog[i];
}

void StoreManager::buyItem(PlayerProfile& player, const string& itemName) {
    for (size_t i = 0; i < catalog.size(); i++) {
        if (catalog[i]->getName() == itemName) {
            if (player.spendCoins(catalog[i]->getPrice())) {
                player.addItem(catalog[i]->clone());
                cout << "[Магазин]: " << player.getName() << " придбав '" << itemName << "'.\n";
            }
			return;
        }
    }
}