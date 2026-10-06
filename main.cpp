#include <iostream>
#include <windows.h>
#include "Ship.h"
#include "FieldManager.h"

#include "PlayerProfile.h"
#include "StoreManager.h"

using namespace std;

int main() {

    SetConsoleCP(65001);
    SetConsoleOutputCP(65001);

    cout << "Початок тестового сценарію роботи магазину, та профілю гравця..." << endl;

    PlayerProfile player1("Ання");
    StoreManager store;

    player1.displayProfile();

    store.displayCatalog();

    store.buyItem(player1, "Міна");
    store.buyItem(player1, "Авіаудар (Літак)");

    cout << "\n--- Імітація ігрового бою ---" << endl;
    player1.recordWin();

    store.buyItem(player1, "Авіаудар (Літак)");

    player1.displayProfile();

    cout << "Цей тестовий сценарій завершено." << endl;



    cout << "тест 1: Клас Ship \n";
    Ship ship1("Катер", 2);
    Ship ship2("Лінкор", 4);

    cout << "Перевірка геттерів: " << ship1.getName() << " (Розмір: " << ship1.getSize() << ")\n";
    cout << "Перевірка геттерів: " << ship2.getName() << " (Розмір: " << ship2.getSize() << ")\n\n";

    cout << "тест 2: Розміщення кораблів \n";
    FieldManager field;

    field.placeShip(ship1, 0, 0, true);
    field.placeShip(ship2, 3, 2, false);

    field.printField();

    cout << "тест 3: Перевірка межі та стану\n";

    bool validPlace = field.canPlace(5, 5, 3, true);
    cout << "Чи можна поставити у (5,5), розмір 3, горизонт: ";
    if (validPlace) {
        cout << "так\n";
    }
    else {
        cout << "ні\n";
    }

    bool invalidPlace = field.canPlace(9, 9, 3, true);
    cout << "Чи можна поставити у (9,9), розмір 3, горизонт (за межі): ";
    if (invalidPlace) {
        cout << "так\n\n";
    }
    else {
        cout << "ні\n\n";
    }

    cout << "тест 4: Постріли по полю \n";

    field.shoot(0, 0);

    field.shoot(5, 5);

    field.shoot(0, 0);

    field.shoot(12, 3);

    cout << "\nСтан поля після всіх дій \n";
    field.printField();

    return 0;
}