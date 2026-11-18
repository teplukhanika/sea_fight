#include "RegistrationManager.h"
#include <iostream>
#include <algorithm>
#include <sstream>
#include <fstream>

using namespace std;

RegistrationManager::RegistrationManager() { players.reserve(100); }

PlayerProfile* RegistrationManager::registerPlayer(const string& name) {
    for (size_t i = 0; i < players.size(); i++) {
        if (players[i].getName() == name) return &players[i];
    }
    players.push_back(PlayerProfile(name));
    cout << "[Реєстрація]: Створено профіль '" << name << "'.\n";
    return &players.back();
}

void RegistrationManager::sortAndPrintLeaderboard() {
    sort(players.begin(), players.end(), [](const PlayerProfile& a, const PlayerProfile& b) {
        if (a.getWins() != b.getWins()) return a.getWins() > b.getWins();
        return a.getBalance() > b.getBalance();
        });
    cout << "\n--- ТАБЛИЦЯ ЛІДЕРІВ (Відсортовано за перемогами) ---\n";
    for (size_t i = 0; i < players.size(); i++) {
        cout << i + 1 << ".";
        players[i].display();
    }
}

string RegistrationManager::saveAllToMemoryBuffer() const {
    stringstream ss;
    for (size_t i = 0; i < players.size(); i++) {
        ss << players[i].serialize() << "\n";
    }
    return ss.str();
}

bool RegistrationManager::saveToFile(const string& path) const {
    ofstream out(path);
    if (!out) {
        cout << "[Збереження]: Не вдалося відкрити файл '" << path << "' для запису.\n";
        return false;
    }
    out << saveAllToMemoryBuffer();
    if (!out) return false;
    cout << "[Збереження]: Збережено профілів: " << players.size() << " -> " << path << "\n";
    return true;
}

bool RegistrationManager::loadFromFile(const string& path) {
    ifstream in(path);
    if (!in) {
        cout << "[Завантаження]: Файл '" << path << "' не знайдено.\n";
        return false;
    }
    vector<PlayerProfile> loaded;
    string line;
    int bad = 0;
    while (getline(in, line)) {
        if (!line.empty() && line.back() == '\r') line.pop_back();
        if (line.empty()) continue;
        PlayerProfile p;
        if (PlayerProfile::deserialize(line, p)) loaded.push_back(p);
        else bad++;
    }
    players = loaded;
    players.reserve(100);
    cout << "[Завантаження]: Відновлено профілів: " << players.size();
    if (bad > 0) cout << " (пропущено пошкоджених рядків: " << bad << ")";
    cout << "\n";
    return true;
}
