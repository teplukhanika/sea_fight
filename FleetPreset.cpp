#include "FleetPreset.h"

using namespace std;

FleetPreset::FleetPreset(string name) {
    presetName = name;
    defaultShips.push_back(new Cruiser());
    defaultShips.push_back(new TankerShip());
    defaultShips.push_back(new MovingBoat());
    defaultShips.push_back(new Submarine());
    defaultShips.push_back(new AirDrone());
}

FleetPreset::~FleetPreset() {
    for (size_t i = 0; i < defaultShips.size(); i++) {
        delete defaultShips[i];
    }
    defaultShips.clear();
}

vector<Ship*> FleetPreset::createFleetCopy() const {
    vector<Ship*> copy;
    for (size_t i = 0; i < defaultShips.size(); i++) {
        copy.push_back(defaultShips[i]->clone());
    }
    return copy;
}


string FleetPreset::getPresetName() const {
    return presetName;
}