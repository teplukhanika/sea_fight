#include "Player.h"
#include <iostream>
#include <limits>
#include <algorithm>
using namespace std;

Player::Player(PlayerProfile* prof) : profile(prof) {}

Player::~Player() {}

string Player::getName() const {
    return profile ? profile->getName() : getPlayerType();
}

PlayerProfile* Player::getProfile() const { return profile; }
FieldManager& Player::getField() { return ownField; }
const FieldManager& Player::getField() const { return ownField; }

void Player::onShotFeedback(int, int, ShotResult) {
}

bool Player::isBot() const { return false; }

void Player::reset() { ownField.clearField(); }

void Player::printInfo() const {
    cout << "  [" << getPlayerType() << "] " << getName()
        << " | Живих кораблів: " << ownField.getAliveShipsCount()
        << (isBot() ? " | керується ШІ" : " | керується людиною") << "\n";
}

HumanPlayer::HumanPlayer(PlayerProfile* prof, bool allowConsoleInput)
    : Player(prof), stepIndex(0), interactive(allowConsoleInput) {
    for (int y = 0; y < 10; y++)
        for (int x = 0; x < 10; x++)
            shotMap[y][x] = false;
}

void HumanPlayer::queuePlannedMove(int x, int y, AttackAction* customAttack) {
    scriptedCoords.push_back({ x, y });
    scriptedAttacks.push_back(customAttack);
}

bool HumanPlayer::hasPlannedMoves() const { return stepIndex < scriptedCoords.size(); }

TurnDecision HumanPlayer::makeTurnDecision(AttackAction* defaultAttack) {
    TurnDecision d;
    if (hasPlannedMoves()) {
        d.x = scriptedCoords[stepIndex].first;
        d.y = scriptedCoords[stepIndex].second;
        d.attack = scriptedAttacks[stepIndex] ? scriptedAttacks[stepIndex] : defaultAttack;
        stepIndex++;
        cout << "[HumanPlayer (" << getName() << ")]: Запланований хід у (" << d.x << "," << d.y << ")\n";
    }
    else if (interactive && cin.good()) {
        d = askFromConsole(defaultAttack);
    }
    else {
        d = fallbackNextCell(defaultAttack);
    }

    if (d.x >= 0 && d.x < 10 && d.y >= 0 && d.y < 10) shotMap[d.y][d.x] = true;
    return d;
}

TurnDecision HumanPlayer::askFromConsole(AttackAction* defaultAttack) {
    int x, y;
    while (true) {
        cout << "[HumanPlayer (" << getName() << ")]: Введіть координати X Y (0-9): ";
        if (cin >> x >> y && x >= 0 && x < 10 && y >= 0 && y < 10) {
            return { x, y, defaultAttack };
        }
        if (cin.eof()) {               // введення закінчилось — не зависаємо
            return fallbackNextCell(defaultAttack);
        }
        cin.clear();
        cin.ignore((numeric_limits<streamsize>::max)(), '\n'); // дужки — захист від макросу max з windows.h
        cout << "  Некоректні координати, спробуйте ще раз.\n";
    }
}

TurnDecision HumanPlayer::fallbackNextCell(AttackAction* defaultAttack) {
    for (int y = 0; y < 10; y++)
        for (int x = 0; x < 10; x++)
            if (!shotMap[y][x]) {
                cout << "[HumanPlayer (" << getName() << ")]: Автохід у (" << x << "," << y << ")\n";
                return { x, y, defaultAttack };
            }
    return { 0, 0, defaultAttack };
}

void HumanPlayer::reset() {
    Player::reset();
    scriptedCoords.clear();
    scriptedAttacks.clear();
    stepIndex = 0;
    for (int y = 0; y < 10; y++)
        for (int x = 0; x < 10; x++)
            shotMap[y][x] = false;
}

EasyBotPlayer::EasyBotPlayer(PlayerProfile* prof, unsigned int seed)
    : Player(prof), rng(seed) {
    reset();
}

void EasyBotPlayer::reset() {
    Player::reset();
    freeCells.clear();
    for (int y = 0; y < 10; y++)
        for (int x = 0; x < 10; x++)
            freeCells.push_back({ x, y });
    shuffle(freeCells.begin(), freeCells.end(), rng);
}

TurnDecision EasyBotPlayer::makeTurnDecision(AttackAction* defaultAttack) {
    if (freeCells.empty()) return { 0, 0, defaultAttack };
    pair<int, int> cell = freeCells.back();
    freeCells.pop_back();
    cout << "[EasyBotPlayer (" << getName() << ")]: Випадковий постріл у ("
        << cell.first << "," << cell.second << ")\n";
    return { cell.first, cell.second, defaultAttack };
}

SmartBotPlayer::SmartBotPlayer(PlayerProfile* prof) : Player(prof) {}

TurnDecision SmartBotPlayer::makeTurnDecision(AttackAction* defaultAttack) {
    pair<int, int> target = brain.makeMove(); // делегування до BotAI
    return { target.first, target.second, defaultAttack };
}

void SmartBotPlayer::onShotFeedback(int x, int y, ShotResult result) {
    brain.notifyShotResult(x, y, result);
}

void SmartBotPlayer::reset() {
    Player::reset();
    brain.reset();
}
