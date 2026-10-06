# sea_fight
//морський бій на мінімалках
#include <iostream>
#include <string>

using namespace std;


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
        cout << "[Ship]: Знищено корабель'" << name << "'\n";
    }

    string getName() const {
        return name;
    }

    int getSize() const {
        return size;
    }

};

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

    void placeShip(const Ship& ship, int x, int y, bool isHorizontal) {
        int s = ship.getSize();

        if (isHorizontal) {
            for (int i = 0; i < s; i++) {
                grid[y][x + i] = 'S';
            }
        }
        else {
            for (int i = 0; i < s; i++) {
                grid[y + i][x] = 'S';
            }
        }

        cout << "[FieldManager]: Поставлено корабель '" << ship.getName()
            << "' у координати (" << x << ", " << y << ")\n";
    }

    void printField() const {

        cout << "\n<<< Ігрове поле (10x10) >>>\n  ";
        for (int x = 0; x < SIZE; x++) {
            cout << x << " ";
        }
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

