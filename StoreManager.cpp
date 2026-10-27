#include "StoreManager.h"

#include <iostream>
#include <iomanip>

StoreManager::StoreManager() {
    catalog.push_back({ "Міна", 3, "Встановлює морську міну на власному полі" });
    catalog.push_back({ "Радар", 5, "Сканує квадрат 3x3 на полі ворога" });
    catalog.push_back({ "Ремкомплект", 6, "Відновлює 1 підбиту палубу корабля" });
    catalog.push_back({ "Авіаудар", 8, "Залп по 3 клітинках у ряд" });
}

void StoreManager::displayCatalog() const {
    cout << "\n|___ МАГАЗИН СПЕЦЗАСОБІВ ___|" << endl;
    for (size_t i = 0; i < catalog.size(); i++) {
        cout << " " << i + 1 << ". " << left << setw(12) << catalog[i].name
            << " | " << catalog[i].price << " монет | " << catalog[i].description << "\n";
    }
    cout << "|___________________________|\n" << endl;
}

void StoreManager::buyItem(PlayerProfile& player, const string& itemName) {
    cout << "[Магазин] Запит на купівлю: '" << itemName << "' гравцем " << player.getName() << "..." << endl;

    for (size_t i = 0; i < catalog.size(); i++) {
        if (catalog[i].name == itemName) {
            if (player.spendCoins(catalog[i].price)) {
                player.addItemToInventory(itemName, 1);
                cout << "[Магазин]: " << player.getName() << " придбав '" << itemName
                    << "' за " << catalog[i].price << " монет (Залишок: " << player.getBalance() << ").\n";
                return true;
            }
            else {
                cout << "[Магазин]: Недостатньо монет для купівлі '" << itemName << "'!\n";
                return false;
            }
        }
    }
    cout << "[Магазин]: Товар '" << itemName << "' не знайдено.\n";
    return false;
}