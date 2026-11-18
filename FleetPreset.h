#pragma once
#include <string>
#include <vector>
#include "Ship.h"

using namespace std;

class FleetPreset {
private:
    string presetName;
    vector<Ship*> defaultShips;

public:
    FleetPreset(string name = "Стандартна ескадра");
    ~FleetPreset();

    vector<Ship*> createFleetCopy() const;
    string getPresetName() const;
};