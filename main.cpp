#include <iostream>
#include <vector>
#include "RegistrationManager.h"
#include "StoreManager.h"
#include "AttackAction.h"
#include "GameModeManager.h"
#ifdef _WIN32
#include <windows.h>
#endif
using namespace std;

int main() {
#ifdef _WIN32
    SetConsoleCP(65001);
    SetConsoleOutputCP(65001);
#endif

    cout << "====================================================================\n";
    cout << "   ЛАБОРАТОРНА РОБОТА №3: УСПАДКУВАННЯ ТА ПОЛІМОРФІЗМ (ПОВНА ГРА)\n";
    cout << "====================================================================\n";

    // 1. Реєстрація та магазин (Яна)
    RegistrationManager reg;
    PlayerProfile* profRoma = reg.registerPlayer("Рома");
    PlayerProfile* profBot = reg.registerPlayer("Кібер-Адмірал");
    reg.registerPlayer("Олексій");

    StoreManager store;
    store.buyItem(*profRoma, "Радар");
    store.buyItem(*profRoma, "Міна");
    store.buyItem(*profRoma, "Ремкомплект");

    // 2. Демонстрація поліморфізму гравців (Нікіта): один масив Player* — різна поведінка
    cout << "\n--- Поліморфна колекція гравців (vector<Player*>) ---\n";
    vector<Player*> lobby;
    lobby.push_back(new HumanPlayer(profRoma));
    lobby.push_back(new EasyBotPlayer(nullptr));
    lobby.push_back(new SmartBotPlayer(profBot));
    for (size_t i = 0; i < lobby.size(); i++) lobby[i]->printInfo(); // віртуальні getPlayerType()/isBot()
    for (size_t i = 0; i < lobby.size(); i++) delete lobby[i];      // віртуальний деструктор
    lobby.clear();

    // 3. Створення матчу PvE: менеджер сам створює потрібні типи гравців
    GameModeManager match;
    match.setupMatch(GameMode::PVE, profRoma, profBot, BotDifficulty::SMART);

    Player* p1 = match.getPlayer1();
    Player* p2 = match.getPlayer2();

    // 4. Розстановка кораблів (Ніка)
    cout << "\n--- Розстановка кораблів Гравця 1 (" << p1->getName() << ") ---\n";
    p1->getField().placeShip(new Cruiser(), 1, 1, true);
    p1->getField().placeShip(new MovingBoat(), 5, 5, true);

    cout << "\n--- Розстановка кораблів Гравця 2 (" << p2->getName() << ") ---\n";
    p2->getField().placeShip(new TankerShip(), 2, 2, true);
    p2->getField().placeShip(new Submarine(), 4, 4, true);
    p2->getField().placeShip(new AirDrone(), 7, 7, true);

    // Поліморфне застосування предметів інвентарю (Яна)
    profRoma->useItem("Міна", p1->getField(), p2->getField(), 0, 0);
    profRoma->useItem("Радар", p1->getField(), p2->getField(), 2, 2);

    // 5. Планування різнотипних атак (Міша)
    SingleShotAttack singleShot;
    CrossVolleyAttack crossVolley;
    DepthChargeAttack depthCharge;
    AntiAirAttack antiAir;

    // queuePlannedMove є тільки в HumanPlayer -> безпечне приведення типу
    if (HumanPlayer* human = dynamic_cast<HumanPlayer*>(p1)) {
        human->queuePlannedMove(9, 9, &singleShot);  // промах -> хід переходить до бота
        human->queuePlannedMove(2, 2, &crossVolley); // танкер
        human->queuePlannedMove(4, 4, &depthCharge); // субмарина
        human->queuePlannedMove(5, 4, &depthCharge);
        human->queuePlannedMove(7, 7, &antiAir);     // дрон
    }

    // 6. Бій
    cout << "\n--- СИМУЛЯЦІЯ ПОЛІМОРФНОГО БОЮ ---\n";
    match.printStatus();
    while (!match.executeNextTurn()) {
        // цикл триває до перемоги однієї зі сторін (або ліміту ходів)
    }
    match.printStatus();

    FieldManager::printSideBySide(p1->getField(), p2->getField(), MapLayer::WATER);

    // 7. Пошук, фільтрація, сортування, серіалізація
    p2->getField().searchShipsByLayer(MapLayer::UNDERWATER);
    match.getCombat().printFilteredHistory(true);
    reg.sortAndPrintLeaderboard();
    cout << "\n[Збереження стану профілів (Серіалізація)]:\n" << reg.saveAllToMemoryBuffer();

    return 0;
}
