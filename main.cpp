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

    bool shoot(int x, int y) {
        if (x < 0 || x >= SIZE || y < 0 || y >= SIZE) {
            cout << "[FieldManager]: Постріл за межі поля:(\n";
            return false;
        }

        if (grid[y][x] == 'S') {
            grid[y][x] = 'X'; 
            cout << "[FieldManager]: :) Влучання у координати (" << x << ", " << y << ")!\n";
            return true;
        }
        else if (grid[y][x] == '~') {
            grid[y][x] = '*'; 
            cout << "[FieldManager]: :( Промах у координати (" << x << ", " << y << ").\n";
            return false;
        }
        else {
            cout << "[FieldManager]: Сюди вже стріляли:(\n";
            return false;
        }
    }

    bool canPlace(int x, int y, int size, bool isHorizontal) const {
        for (int i = 0; i < size; i++) {
            int cx = x;
            int cy = y;

            if (isHorizontal) {
                cx = x + i;
            }
            else {
                cy = y + i;
            }

            
            if (cx < 0 || cx >= SIZE || cy < 0 || cy >= SIZE) {
                return false;
            }

            //метод перевірки розташування поруч корабля
        }
        return true; 
    }
};

