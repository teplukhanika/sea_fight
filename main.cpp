#include <iostream>
#include <string>

using namespace std;

// ==========================================
// 1. КЛАС: Ship (Базовий об'єкт)
// ==========================================
class Ship {
private:
    string name;
    int size;

public:
    Ship(string shipName, int shipSize) {
        name = shipName;
        size = shipSize;
        cout << "[Ship]: Створено корабель '" << name << "' (Розмір: " << size << ")\n";
    }

    ~Ship() {
        cout << "[Ship]: Знищено корабель '" << name << "'\n";
    }

    string getName() const { return name; }
    int getSize() const { return size; }
};
     
// ==========================================
// 2. КЛАС: FieldManager (Менеджер поля)
// ==========================================
class FieldManager {
private:
    static const int SIZE = 10;
    char grid[SIZE][SIZE];

public:
    FieldManager() {
        for (int r = 0; r < SIZE; r++) {
            for (int c = 0; c < SIZE; c++) {
                grid[r][c] = '~';
            }
        }
        cout << "[FieldManager]: Створено порожнє поле 10x10.\n";
    }

    ~FieldManager() {
        cout << "[FieldManager]: Ігрове поле знищено.\n";
    }

    bool placeShip(const Ship& ship, int x, int y, bool isHorizontal) {
        int s = ship.getSize();

        if (isHorizontal) {
            if (x < 0 || x + s > SIZE || y < 0 || y >= SIZE) {
                cout << "[ПОМИЛКА]: Корабель виходить за межі поля!\n";
                return false;
            }
            for (int i = 0; i < s; i++) {
                grid[y][x + i] = 'S';
            }
        }
        else {
            if (y < 0 || y + s > SIZE || x < 0 || x >= SIZE) {
                cout << "[ПОМИЛКА]: Корабель виходить за межі поля!\n";
                return false;
            }
            for (int i = 0; i < s; i++) {
                grid[y + i][x] = 'S';
            }
        }

        cout << "[FieldManager]: Успішно поставлено '" << ship.getName()
            << "' у координати (" << x << ", " << y << ")\n";
        return true;
    }

    void printField() const {
        cout << "\n=== ІГРОВЕ ПОЛЕ (10x10) ===\n  ";
        for (int x = 0; x < SIZE; x++) cout << x << " ";
        cout << "\n";

        for (int y = 0; y < SIZE; y++) {
            cout << y << " ";
            for (int x = 0; x < SIZE; x++) {
                cout << grid[y][x] << " ";
            }
            cout << "\n";
        }
        cout << "---------------------------\n\n";
    }
};

// ==========================================
// 3. ФУНКЦІЯ ЮНІТ-ТЕСТІВ
// ==========================================
void runTests() {
    cout << "\n=== ЗАПУСК АВТОМАТИЧНИХ ТЕСТІВ ===\n";
    FieldManager testField;
    Ship testBoat("Тестовий Човен", 2);

    cout << "\n-- Тест 1: Успішне розміщення --\n";
    testField.placeShip(testBoat, 0, 0, true);

    cout << "\n-- Тест 2: Вихід за межі поля --\n";
    testField.placeShip(testBoat, 9, 9, true);

    cout << "\n=== ТЕСТИ ЗАВЕРШЕНО ===\n\n";
}

