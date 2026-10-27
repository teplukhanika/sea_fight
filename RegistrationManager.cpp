#include "RegistrationManager.h"
#include <iostream>

using namespace std;

RegistrationManager::RegistrationManager() {
    registeredPlayers.reserve(100);
}

PlayerProfile* RegistrationManager::registerOrLogin(const string& playerName) {

}