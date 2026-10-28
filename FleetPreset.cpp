#include "FleetPreset.h"

using namespace std;

FleetPreset::FleetPreset(string name) {
    presetName = name;

    defaultShips.push_back(Ship("Лінкор", 4, MapLayer::WATER, false, true));
    defaultShips.push_back(Ship("Крейсер", 3, MapLayer::WATER, false, true));
    defaultShips.push_back(Ship("Танкер", 2, MapLayer::WATER, true, false));
    defaultShips.push_back(Ship("Катер", 1, MapLayer::WATER, false, false));
    defaultShips.push_back(Ship("Субмарина", 2, MapLayer::UNDERWATER, false, false));
    defaultShips.push_back(Ship("Авіадрон", 1, MapLayer::AIR, false, false));
}

const vector<Ship>& FleetPreset::getShips() const {
    return defaultShips;
}

string FleetPreset::getPresetName() const {
    return presetName;
}