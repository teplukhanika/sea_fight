#pragma once
#include <string>
#include <vector>
#include "Ship.h"

using namespace std;

class FleetPreset {
private:
    string presetName;
    vector<Ship> defaultShips;

public:
    FleetPreset(string name = "Стандартна ескадра");

    const vector<Ship>& getShips() const;
    string getPresetName() const;
};