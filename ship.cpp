#include "Ship.h"
#include <iostream>

using namespace std;

Ship::Ship(string shipName, int shipSize) {
    name = shipName;
    size = shipSize;
    cout << "[Ship]: Створено корабель '" << name << "' (Розмір: " << size << ")\n";
}

Ship::~Ship() {
    cout << "[Ship]: Знищено корабель'" << name << "'\n";
}

string Ship::getName() const {
    return name;
}

int Ship::getSize() const {
    return size;
}