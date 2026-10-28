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

bool FieldManager::placeShip(Ship ship, int x, int y, bool isHorizontal) {
    MapLayer layer = ship.getLayer();

    if (!canPlace(x, y, ship.getSize(), isHorizontal, layer)) {
        return false;
    }

    int l = static_cast<int>(layer);
    ship.setPosition(x, y, isHorizontal);
    ships.push_back(ship);

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

void FieldManager::autoPlaceFleet(const FleetPreset& preset, int seedOffset) {
    const vector<Ship>& fleet = preset.getShips();

    int coords[6][3] = {
        { 0, (0 + seedOffset) % 8, 1 },
        { 5, (1 + seedOffset) % 8, 1 },
        { 1, (4 + seedOffset) % 8, 0 },
        { 8, (6 + seedOffset) % 8, 1 },
        { 2, (2 + seedOffset) % 7, 1 },
        { 7, (7 + seedOffset) % 9, 1 }
    };

    for (size_t i = 0; i < fleet.size(); i++) {
        bool placed = placeShip(fleet[i], coords[i][0], coords[i][1], coords[i][2] == 1);
        if (!placed) {
            for (int y = 0; y < SIZE && !placed; y++) {
                for (int x = 0; x < SIZE && !placed; x++) {
                    placed = placeShip(fleet[i], x, y, true);
                }
            }
        }
    }
    cout << "[FieldManager]: Автоматично розставлено ескадру '" << preset.getPresetName() << "'.\n";
}

bool FieldManager::placeMine(int x, int y, MapLayer layer) {
    int l = static_cast<int>(layer);

    if (!isInside(x, y) || grid[l][y][x] != '~') {
        return false;
    }

    mines.push_back(SeaMine(x, y, layer));
    grid[l][y][x] = 'M';
    cout << "[FieldManager]: Встановлено морську міну у (" << x << ", " << y << ").\n";
    return true;
}

bool FieldManager::moveShip(size_t shipIndex, int dx, int dy) {
    if (shipIndex >= ships.size()) return false;

    Ship& s = ships[shipIndex];
    if (s.getHits() > 0) {
        cout << "[FieldManager]: Пошкоджений корабель не може рухатись!\n";
        return false;
    }

    int l = static_cast<int>(s.getLayer());
    vector<pair<int, int>> oldCells = s.getOccupiedCells();

    for (size_t i = 0; i < oldCells.size(); i++) {
        grid[l][oldCells[i].second][oldCells[i].first] = '~';
    }

    int newX = s.getStartX() + dx;
    int newY = s.getStartY() + dy;

    if (canPlace(newX, newY, s.getSize(), s.getIsHorizontal(), s.getLayer())) {
        s.setPosition(newX, newY, s.getIsHorizontal());
        vector<pair<int, int>> newCells = s.getOccupiedCells();
        for (size_t i = 0; i < newCells.size(); i++) {
            grid[l][newCells[i].second][newCells[i].first] = 'S';
        }
        cout << "[FieldManager]: Корабель перемістився у (" << newX << ", " << newY << ").\n";
        return true;
    }
    else {
        for (size_t i = 0; i < oldCells.size(); i++) {
            grid[l][oldCells[i].second][oldCells[i].first] = 'S';
        }
        return false;
    }
}

bool FieldManager::repairDamagedShip() {
    for (size_t i = 0; i < ships.size(); i++) {
        if (ships[i].repairOneDeck()) {
            int l = static_cast<int>(ships[i].getLayer());
            vector<pair<int, int>> cells = ships[i].getOccupiedCells();
            for (size_t c = 0; c < cells.size(); c++) {
                if (grid[l][cells[c].second][cells[c].first] == 'X') {
                    grid[l][cells[c].second][cells[c].first] = 'S';
                    break;
                }
            }
            cout << "[FieldManager]: Відремонтовано 1 палубу корабля '" << ships[i].getName() << "'!\n";
            return true;
        }
    }
    return false;
}

int FieldManager::scanArea(int centerX, int centerY, MapLayer layer) const {
    int l = static_cast<int>(layer);
    int detectedDecks = 0;

    for (int dy = -1; dy <= 1; dy++) {
        for (int dx = -1; dx <= 1; dx++) {
            int nx = centerX + dx;
            int ny = centerY + dy;
            if (isInside(nx, ny) && (grid[l][ny][nx] == 'S' || grid[l][ny][nx] == 'M')) {
                detectedDecks++;
            }
        }
    }
    return detectedDecks;
}

int FieldManager::shoot(int x, int y, MapLayer layer, Ship** outDestroyedShip) {
    if (x < 0 || x >= SIZE || y < 0 || y >= SIZE) {
        cout << "[FieldManager]: Постріл за межі поля:(\n";
        return -1;
    }

    int l = static_cast<int>(layer);

    if (grid[l][y][x] == 'M') {
        grid[l][y][x] = 'X';
        for (size_t i = 0; i < mines.size(); i++) {
            if (mines[i].getX() == x && mines[i].getY() == y && mines[i].getLayer() == layer) {
                mines[i].detonate();
                break;
            }
        }
        cout << "[FieldManager]: ВИБУХ МОРСЬКОЇ МІНИ у координатах (" << x << ", " << y << ")!\n";
        return 3;
    }

    if (grid[l][y][x] == 'S') {
        grid[l][y][x] = 'X';
        cout << "[FieldManager]: :) Влучання у координати (" << x << ", " << y << ")!\n";

        for (size_t i = 0; i < ships.size(); i++) {
            if (ships[i].occupies(x, y, layer)) {
                ships[i].hit();
                if (ships[i].isDestroyed()) {
                    if (outDestroyedShip != nullptr) {
                        *outDestroyedShip = &ships[i];
                    }
                    cout << "[FieldManager]: Корабель знищено!\n";
                    return 2;
                }
                return 1;
            }
        }
        return 1;
    }
    else if (grid[l][y][x] == '~') {
        grid[l][y][x] = '*';
        cout << "[FieldManager]: :( Промах у координати (" << x << ", " << y << ").\n";
        return 0;
    }
    else {
        cout << "[FieldManager]: Сюди вже стріляли:(\n";
        return -1;
    }
}

void FieldManager::markCellAround(int x, int y, MapLayer layer) {
    int l = static_cast<int>(layer);
    if (isInside(x, y) && grid[l][y][x] == '~') {
        grid[l][y][x] = '*';
    }
}

int FieldManager::getAliveShipsCount() const {
    int alive = 0;
    for (size_t i = 0; i < ships.size(); i++) {
        if (!ships[i].isDestroyed()) {
            alive++;
        }
    }
    return alive;
}

bool FieldManager::areAllShipsDestroyed() const {
    return !ships.empty() && getAliveShipsCount() == 0;
}

void FieldManager::printField(MapLayer layer, bool fogOfWar) const {
    int l = static_cast<int>(layer);

    cout << "\n<<< Ігрове поле (10x10) | Шар " << l << " >>>\n  ";
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

void FieldManager::printSideBySide(const FieldManager& ownField, const FieldManager& enemyField, MapLayer layer) {
    int l = static_cast<int>(layer);

    cout << "\n  --- ВЛАСНЕ ПОЛЕ ---                  --- ПОЛЕ ВОРОГА ---\n";
    cout << "  0 1 2 3 4 5 6 7 8 9                  0 1 2 3 4 5 6 7 8 9\n";

    for (int y = 0; y < SIZE; y++) {
        cout << y << " ";
        for (int x = 0; x < SIZE; x++) {
            cout << ownField.grid[l][y][x] << " ";
        }

        cout << "                 " << y << " ";

        for (int x = 0; x < SIZE; x++) {
            char c = enemyField.grid[l][y][x];
            if (c == 'S' || c == 'M') {
                c = '~';
            }
            cout << c << " ";
        }
        cout << "\n";
    }
    cout << "----------------------------------------------------------\n\n";
}