#include "FieldManager.h"
#include <iostream>
#include <algorithm>

using namespace std;

FieldManager::FieldManager() {
    for (int l = 0; l < LAYERS; l++)
        for (int r = 0; r < SIZE; r++)
            for (int c = 0; c < SIZE; c++)
                grid[l][r][c] = '~';
}

FieldManager::~FieldManager() {
    clearField();
}

void FieldManager::clearField() {
    for (size_t i = 0; i < ships.size(); i++) {
        delete ships[i];
    }
    ships.clear();
    mines.clear();
    for (int l = 0; l < LAYERS; l++)
        for (int r = 0; r < SIZE; r++)
            for (int c = 0; c < SIZE; c++)
                grid[l][r][c] = '~';
}

bool FieldManager::isInside(int x, int y) const {
    return x >= 0 && x < SIZE && y >= 0 && y < SIZE;
}

bool FieldManager::canPlace(int x, int y, int size, bool isHorizontal, MapLayer layer) const {
    int l = static_cast<int>(layer);
    for (int i = 0; i < size; i++) {
        int cx = isHorizontal ? x + i : x;
        int cy = isHorizontal ? y : y + i;
        if (!isInside(cx, cy)) return false;

        for (int dy = -1; dy <= 1; dy++) {
            for (int dx = -1; dx <= 1; dx++) {
                int nx = cx + dx, ny = cy + dy;
                if (isInside(nx, ny)) {
                    char c = grid[l][ny][nx];
                    if (c != '~' && c != '*' && c != 'X') return false;
                }
            }
        }
    }
    return true;
}

bool FieldManager::placeShip(Ship* ship, int x, int y, bool isHorizontal) {
    if (!canPlace(x, y, ship->getSize(), isHorizontal, ship->getLayer())) {
        delete ship;
        return false;
    }
    int l = static_cast<int>(ship->getLayer());
    ship->setPosition(x, y, isHorizontal);
    ships.push_back(ship);

    for (int i = 0; i < ship->getSize(); i++) {
        int cx = isHorizontal ? x + i : x;
        int cy = isHorizontal ? y : y + i;
        grid[l][cy][cx] = ship->getSymbol(); 
    }
    cout << "[FieldManager]: Розміщено '" << ship->getName() << "' [" << ship->getSymbol()
        << "] у (" << x << ", " << y << ") [Шар " << l << "]\n";
    return true;
}

void FieldManager::autoPlaceFleet(const FleetPreset& preset, int seedOffset) {
    vector<Ship*> fleet = preset.createFleetCopy();
    int coords[5][3] = {
        { 1, (1 + seedOffset) % 8, 1 },
        { 5, (2 + seedOffset) % 8, 1 },
        { 2, (5 + seedOffset) % 8, 1 },
        { 0, (4 + seedOffset) % 7, 1 },
        { 7, (7 + seedOffset) % 9, 1 }
    };
    for (size_t i = 0; i < fleet.size(); i++) {
        Ship* s = fleet[i];
        Ship* backupClone = s->clone();
        bool placed = placeShip(s, coords[i % 5][0], coords[i % 5][1], coords[i % 5][2] == 1);
        if (!placed) {
            for (int y = 0; y < SIZE && !placed; y++) {
                for (int x = 0; x < SIZE && !placed; x++) {
                    Ship* retryClone = backupClone->clone();
                    placed = placeShip(retryClone, x, y, true);
                }
            }
        }
        delete backupClone;
    }
    cout << "[FieldManager]: Автоматично розставлено поліморфну ескадру '" << preset.getPresetName() << "'.\n";
}

bool FieldManager::placeMine(int x, int y, MapLayer layer) {
    int l = static_cast<int>(layer);
    if (!isInside(x, y) || grid[l][y][x] != '~') return false;
    mines.push_back(SeaMine(x, y, layer));
    grid[l][y][x] = 'M';
    return true;
}

bool FieldManager::tryShiftSingleCellShip(Ship* ship, int dx, int dy) {
    if (!ship->canMove()) return false;
    int l = static_cast<int>(ship->getLayer());
    int oldX = ship->getStartX(), oldY = ship->getStartY();
    int newX = oldX + dx, newY = oldY + dy;

    grid[l][oldY][oldX] = '~';
    if (canPlace(newX, newY, ship->getSize(), ship->getIsHorizontal(), ship->getLayer())) {
        ship->setPosition(newX, newY, ship->getIsHorizontal());
        grid[l][newY][newX] = ship->getSymbol();
        cout << "  -> [Маневр MovingBoat]: Катер змістився з (" << oldX << ", " << oldY
            << ") у (" << newX << ", " << newY << ")!\n";
        return true;
    }
    grid[l][oldY][oldX] = ship->getSymbol();
    return false;
}

void FieldManager::updateMovingShips() {
    for (size_t i = 0; i < ships.size(); i++) {
        ships[i]->onTurnEnd(*this); // Поліморфне оновлення рухомих кораблів
    }
}

bool FieldManager::repairFirstDamagedShip() {
    for (size_t i = 0; i < ships.size(); i++) {
        if (ships[i]->repairOneDeck()) {
            int l = static_cast<int>(ships[i]->getLayer());
            vector<pair<int, int>> cells = ships[i]->getOccupiedCells();
            for (size_t c = 0; c < cells.size(); c++) {
                if (grid[l][cells[c].second][cells[c].first] == 'X') {
                    grid[l][cells[c].second][cells[c].first] = ships[i]->getSymbol();
                    break;
                }
            }
            cout << "[Ремонт]: Відновлено палубу корабля '" << ships[i]->getName() << "'!\n";
            return true;
        }
    }
    return false;
}

int FieldManager::scanRadar(int cx, int cy, MapLayer layer) const {
    int l = static_cast<int>(layer), count = 0;
    for (int dy = -1; dy <= 1; dy++)
        for (int dx = -1; dx <= 1; dx++)
            if (isInside(cx + dx, cy + dy)) {
                char c = grid[l][cy + dy][cx + dx];
                if (c != '~' && c != '*' && c != 'X') count++;
            }
    return count;
}

int FieldManager::shoot(int x, int y, MapLayer layer, Ship** outDestroyed, FieldManager* attackerField) {
    if (!isInside(x, y)) return -1;
    int l = static_cast<int>(layer);
    char cell = grid[l][y][x];

    if (cell == 'M') {
        grid[l][y][x] = 'X';
        for (size_t i = 0; i < mines.size(); i++) {
            if (mines[i].getX() == x && mines[i].getY() == y && mines[i].getLayer() == layer) {
                mines[i].detonate();
                break;
            }
        }
        cout << "[FieldManager]: ПІДРИВ НА МОРСЬКІЙ МІНІ у (" << x << ", " << y << ")!\n";
        return 3;
    }

    if (cell != '~' && cell != '*' && cell != 'X') {
        grid[l][y][x] = 'X';
        for (size_t i = 0; i < ships.size(); i++) {
            if (ships[i]->occupies(x, y, layer)) {
                ships[i]->hit();
                if (ships[i]->isDestroyed()) {
                    if (outDestroyed) *outDestroyed = ships[i];
                    ships[i]->onDestroy(*this, attackerField); // Поліморфна дія при знищенні!
                    return 2;
                }
                return 1;
            }
        }
        return 1;
    }
    else if (cell == '~') {
        grid[l][y][x] = '*';
        return 0;
    }
    return -1;
}

void FieldManager::markCellAround(int x, int y, MapLayer layer) {
    int l = static_cast<int>(layer);
    if (isInside(x, y) && grid[l][y][x] == '~') grid[l][y][x] = '*';
}

int FieldManager::getAliveShipsCount() const {
    int alive = 0;
    for (size_t i = 0; i < ships.size(); i++)
        if (!ships[i]->isDestroyed()) alive++;
    return alive;
}

bool FieldManager::areAllShipsDestroyed() const {
    return !ships.empty() && getAliveShipsCount() == 0;
}

void FieldManager::searchShipsByLayer(MapLayer layer) const {
    cout << "  Кораблі на шарі " << static_cast<int>(layer) << ": ";
    for (size_t i = 0; i < ships.size(); i++) {
        if (ships[i]->getLayer() == layer) {
            cout << ships[i]->getName() << "(" << (ships[i]->isDestroyed() ? "Знищений" : "Живий") << ") ";
        }
    }
    cout << "\n";
}

void FieldManager::sortShipsBySize() {
    sort(ships.begin(), ships.end(), [](const Ship* a, const Ship* b) {
        return a->getSize() > b->getSize();
        });
}

void FieldManager::printField(MapLayer layer, bool fogOfWar) const {
    int l = static_cast<int>(layer);
    cout << "\n<<< Ігрове поле (10x10) | Шар " << l << " >>>\n  ";
    for (int x = 0; x < SIZE; x++) cout << x << " ";
    cout << "\n";
    for (int y = 0; y < SIZE; y++) {
        cout << y << " ";
        for (int x = 0; x < SIZE; x++) {
            char c = grid[l][y][x];
            if (fogOfWar && c != '~' && c != '*' && c != 'X') c = '~';
            cout << c << " ";
        }
        cout << "\n";
    }
}

void FieldManager::printSideBySide(const FieldManager& own, const FieldManager& enemy, MapLayer layer) {
    int l = static_cast<int>(layer);
    cout << "\n  --- ВЛАСНЕ ПОЛЕ (Живих: " << own.getAliveShipsCount() << ") ---          --- ПОЛЕ ВОРОГА (Туман війни) ---\n";
    cout << "  0 1 2 3 4 5 6 7 8 9             0 1 2 3 4 5 6 7 8 9\n";
    for (int y = 0; y < SIZE; y++) {
        cout << y << " ";
        for (int x = 0; x < SIZE; x++) cout << own.grid[l][y][x] << " ";
        cout << "          " << y << " ";
        for (int x = 0; x < SIZE; x++) {
            char c = enemy.grid[l][y][x];
            if (c != '~' && c != '*' && c != 'X') c = '~';
            cout << c << " ";
        }
        cout << "\n";
    }
}
