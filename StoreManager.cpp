#include "StoreManager.h"

#include <iostream>
#include <iomanip>

StoreManager::StoreManager() {
    catalog["Міна"] = 3;
    catalog["Радар"] = 5;
    catalog["Авіаудар"] = 8;
}

void StoreManager::displayCatalog() const {
    cout << "\n|___ МАГАЗИН СПЕЦЗАСОБІВ ___|" << endl;
    for (const auto& item : catalog) {
        cout << item.first << " | Ціна: " << item.second << " монет" << endl;
    }
    cout << "|___________________________|\n" << endl;
}

void StoreManager::buyItem(PlayerProfile& player, const string& itemName) {
    cout << "[Магазин] Запит на купівлю: '" << itemName << "' гравцем " << player.getName() << "..." << endl;

    auto it = catalog.find(itemName);
    if (it == catalog.end()) {
        cout << "[Помилка] Товару '" << itemName << "' не існує в магазині." << endl;
        return;
    }

    int price = it->second;

    if (player.spendCoins(price)) {
        player.addItemToInventory(itemName, 1);
        cout << "[Успіх] Куплено '" << itemName << "' за " << price << " монет. Залишок: " << player.getBalance() << " монет." << endl;
    }
    else {
        cout << "[Відмова] Недостатньо монет! Потрібно: " << price << ", на балансі: " << player.getBalance() << "." << endl;
    }
}