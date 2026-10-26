#include "FieldManager.h"
#include <iostream>

using namespace std;

FieldManager::FieldManager() {
    clearField();
    cout << "[FieldManager]: Створено порожнє багатошарове поле 10x10.\n";
}

FieldManager::~FieldManager() {
    cout << "[FieldManager]: Ігрове поле знищено.\n";
}
void FieldManager::clearField() {
    ships.clear();
    mines.clear();
    for (int l = 0; l < LAYERS; l++) {
        for (int r = 0; r < SIZE; r++) {
            for (int c = 0; c < SIZE; c++) {
                grid[l][r][c] = '~';
            }
        }
    }
}

bool FieldManager::isInside(int x, int y) const {
    if (x < 0 || x >= SIZE || y < 0 || y >= SIZE) {
        return false;
    }
    return true;
}
void FieldManager::placeShip(const Ship& ship, int x, int y, bool isHorizontal) {
    MapLayer layer = ship.getLayer();

    if (!canPlace(x, y, ship.getSize(), isHorizontal, layer)) {
        return false;
    }

    int l = static_cast<int>(layer);
    ship.setPosition(x, y, isHorizontal);
    ships.push_back(ship); // Зберігаємо об'єкт корабля

    for (int i = 0; i < ship.getSize(); i++) {
        int cx = x;
        int cy = y;

        if (isHorizontal) {
            cx = x + i;
        }
        else {
            cy = y + i;
        }

        grid[l][cy][cx] = 'S';
    }

    cout << "[FieldManager]: Поставлено корабель '" << ship.getName()
        << "' у координати (" << x << ", " << y << ")\n";

    return true;
}

void FieldManager::printField(MapLayer layer, bool fogOfWar) const {
    cout << "\n<<< Ігрове поле (10x10) >>>\n  ";
    for (int x = 0; x < SIZE; x++) {
        cout << x << " ";
    }
    cout << "\n";

    for (int y = 0; y < SIZE; y++) {
        cout << y << " ";
        for (int x = 0; x < SIZE; x++) {
            char c = grid[l][y][x];
            if (fogOfWar && (c == 'S' || c == 'M')) {
                c = '~';
            }
            cout << c << " ";
        }
        cout << "\n";
    }
    cout << "---------------------------\n\n";
}

bool FieldManager::shoot(int x, int y) {
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

bool FieldManager::canPlace(int x, int y, int size, bool isHorizontal, MapLayer layer) const {
    int l = static_cast<int>(layer);
    for (int i = 0; i < size; i++) {
        int cx = x;
        int cy = y;

        if (isHorizontal) {
            cx = x + i;
        }
        else {
            cy = y + i;
        }
        if (!isInside(cx, cy)) {
            return false;
        }

        // Перевірка буферної зони навколо корабля
        for (int dy = -1; dy <= 1; dy++) {
            for (int dx = -1; dx <= 1; dx++) {
                int nx = cx + dx;
                int ny = cy + dy;
                if (isInside(nx, ny)) {
                    if (grid[l][ny][nx] == 'S') {
                        return false;
                    }
                }
            }
        }
    }
    return true;
}