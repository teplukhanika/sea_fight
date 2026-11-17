#include "ShopItem.h"
#include "FieldManager.h"
#include <iostream>

using namespace std;

ShopItem::ShopItem(const string& n, int p) : name(n), price(p) {}
ShopItem::~ShopItem() {}
string ShopItem::getName() const { return name; }
int ShopItem::getPrice() const { return price; }

RadarItem::RadarItem() : ShopItem("Радар", 5) {}
ShopItem* RadarItem::clone() const { return new RadarItem(*this); }
void RadarItem::applyEffect(FieldManager& ownField, FieldManager& enemyField, int x, int y) const {
    int found = enemyField.scanRadar(x, y, MapLayer::WATER);
    cout << "[Поліморфізм RadarItem]: Сканування 3x3 навколо (" << x << "," << y
        << ") виявило об'єктів: " << found << " шт.\n";
}

SeaMineItem::SeaMineItem() : ShopItem("Міна", 3) {}
ShopItem* SeaMineItem::clone() const { return new SeaMineItem(*this); }
void SeaMineItem::applyEffect(FieldManager& ownField, FieldManager& enemyField, int x, int y) const {
    ownField.placeMine(x, y, MapLayer::WATER);
    cout << "[Поліморфізм SeaMineItem]: Морську міну встановлено на власному полі у ("
        << x << "," << y << ")!\n";
}

RepairKitItem::RepairKitItem() : ShopItem("Ремкомплект", 6) {}
ShopItem* RepairKitItem::clone() const { return new RepairKitItem(*this); }
void RepairKitItem::applyEffect(FieldManager& ownField, FieldManager& enemyField, int x, int y) const {
    cout << "[Поліморфізм RepairKitItem]: Запуск ремонтних бригад на власному полі...\n";
    ownField.repairFirstDamagedShip();
}

ShopItem* createShopItem(const string& name) {
    if (name == "Радар")       return new RadarItem();
    if (name == "Міна")        return new SeaMineItem();
    if (name == "Ремкомплект") return new RepairKitItem();
    return nullptr;
}