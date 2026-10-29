#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <iomanip>
#ifdef _WIN32
#include <windows.h>
#endif

// Частина 1: Ніка
#include "SeaMine.h"
#include "Ship.h"
#include "FleetPreset.h"
#include "FieldManager.h"

// Частина 2: Міша
#include "MoveRecord.h"
#include "CombatManager.h"

// Частина 4: Яна
#include "PlayerProfile.h"
#include "RegistrationManager.h"
#include "StoreManager.h"

// Частина 3: Нікіта
#include "BotAI.h"
#include "GameModeManager.h"

using namespace std;

int main() {

    SetConsoleCP(65001);
    SetConsoleOutputCP(65001);

    // Яна
    RegistrationManager regManager;
    PlayerProfile* roma = regManager.registerOrLogin("Рома");
    PlayerProfile* nika = regManager.registerOrLogin("Ніка");
    regManager.printAllProfiles();

    StoreManager store;
    store.displayCatalog();
    store.buyItem(*roma, "Радар");
    store.buyItem(*roma, "Міна");
    store.buyItem(*roma, "Ремкомплект");
    roma->displayProfile();

	// Ніка і Нікіта
    GameModeManager game;
    game.setupMatch(GameMode::PVE, roma);

    game.getField1().placeShip(Ship("Крейсер Роми", 2, MapLayer::WATER, false, true), 1, 1, true);
    game.getField1().placeShip(Ship("Катер Роми", 1, MapLayer::WATER, false, false), 5, 5, true);

    game.getField2().placeShip(Ship("Танкер Бота", 2, MapLayer::WATER, true, false), 2, 2, true);
    game.getField2().placeShip(Ship("Субмарина Бота", 2, MapLayer::UNDERWATER, false, false), 0, 0, true);

    roma->useInventoryItem("Міна", game.getField1(), game.getField2(), 0, 0);
    roma->useInventoryItem("Радар", game.getField1(), game.getField2(), 2, 2);

    game.getField1().moveShip(1, 1, 0);

    FieldManager::printSideBySide(game.getField1(), game.getField2(), MapLayer::WATER);

	// Міша і Нікіта
    cout << "\n--- ПОЧАТОК БОЙОВИХ ДІЙ ---\n";
    game.playTurn(0, 5, MapLayer::WATER);
    game.playTurn(0, 0, MapLayer::WATER);

    game.playTurn(2, 2, MapLayer::WATER);
    game.playTurn(3, 2, MapLayer::WATER);

    game.playTurn(0, 0, MapLayer::UNDERWATER);
    game.playTurn(1, 0, MapLayer::UNDERWATER);

    FieldManager::printSideBySide(game.getField1(), game.getField2(), MapLayer::WATER);
    game.getCombat().printHistory();
    roma->displayProfile();

    return 0;
}