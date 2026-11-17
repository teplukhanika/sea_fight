#pragma once
#include <string>

class FieldManager;

class ShopItem {
protected:
    std::string name;
    int price;
public:
    ShopItem(const std::string& n, int p);
    virtual ~ShopItem();

    std::string getName() const;
    int getPrice() const;

    virtual ShopItem* clone() const = 0;
    virtual void applyEffect(FieldManager& ownField, FieldManager& enemyField, int x, int y) const = 0;
};

class RadarItem : public ShopItem {
public:
    RadarItem();
    ShopItem* clone() const override;
    void applyEffect(FieldManager& ownField, FieldManager& enemyField, int x, int y) const override;
};

class SeaMineItem : public ShopItem {
public:
    SeaMineItem();
    ShopItem* clone() const override;
    void applyEffect(FieldManager& ownField, FieldManager& enemyField, int x, int y) const override;
};

class RepairKitItem : public ShopItem {
public:
    RepairKitItem();
    ShopItem* clone() const override;
    void applyEffect(FieldManager& ownField, FieldManager& enemyField, int x, int y) const override;
};

ShopItem* createShopItem(const std::string& name);