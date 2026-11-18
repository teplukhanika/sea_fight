#pragma once
#include <string>
#include "FieldManager.h"

using namespace std;


class AttackAction {
public:
    virtual ~AttackAction() {}
    virtual string getAttackName() const = 0;
    virtual int execute(FieldManager& targetField, FieldManager* attackerField, int x, int y, Ship** outDestroyed) = 0;
};

class SingleShotAttack : public AttackAction {
public:
    string getAttackName() const override;
    int execute(FieldManager& targetField, FieldManager* attackerField, int x, int y, Ship** outDestroyed) override;
};


class DepthChargeAttack : public AttackAction {
public:
    string getAttackName() const override;
    int execute(FieldManager& targetField, FieldManager* attackerField, int x, int y, Ship** outDestroyed) override;
};


class AntiAirAttack : public AttackAction {
public:
    string getAttackName() const override;
    int execute(FieldManager& targetField, FieldManager* attackerField, int x, int y, Ship** outDestroyed) override;
};


class CrossVolleyAttack : public AttackAction {
public:
    string getAttackName() const override;
    int execute(FieldManager& targetField, FieldManager* attackerField, int x, int y, Ship** outDestroyed) override;
};