#include "RegistrationManager.h"
#include <iostream>

using namespace std;

RegistrationManager::RegistrationManager() {
    registeredPlayers.reserve(100);
}

PlayerProfile* RegistrationManager::registerOrLogin(const string& playerName) {
    if (playerName.empty()) {
        cout << "[Реєстрація]: Ім'я не може бути порожнім!\n";
        return nullptr;
    }
    for (size_t i = 0; i < registeredPlayers.size(); i++) {
        if (registeredPlayers[i].getName() == playerName) {
            cout << "[Авторизація]: З поверненням, " << playerName << " (" << registeredPlayers[i].getRank() << ")!\n";
            return &registeredPlayers[i];
        }
    }
    registeredPlayers.push_back(PlayerProfile(playerName));
    cout << "[Реєстрація]: Створено новий профіль '" << playerName << "' (Стартовий баланс: 15 монет).\n";
    return &registeredPlayers.back();
}

PlayerProfile* RegistrationManager::findPlayer(const string& playerName) {
    for (size_t i = 0; i < registeredPlayers.size(); i++) {
        if (registeredPlayers[i].getName() == playerName) return &registeredPlayers[i];
    }
    return nullptr;
}

void RegistrationManager::printAllProfiles() const {
    cout << "\n--- БАЗА ЗАРЕЄСТРОВАНИХ ГРАВЦІВ (" << registeredPlayers.size() << ") ---\n";
    for (size_t i = 0; i < registeredPlayers.size(); i++) {
        cout << i + 1 << ". " << registeredPlayers[i].getName()
            << " [" << registeredPlayers[i].getRank() << "] — Монет: "
            << registeredPlayers[i].getBalance() << ", Перемог: " << registeredPlayers[i].getWins() << "\n";
    }
}