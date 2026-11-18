#include "GameModeManager.h"
#include <iostream>
using namespace std;

GameModeManager::GameModeManager()
    : currentMode(GameMode::NOT_SELECTED), currentTurn(TurnOwner::PLAYER_1),
    roundNumber(0), turnCounter(0), isGameActive(false) {
}

Player* GameModeManager::attacker() const {
    return currentTurn == TurnOwner::PLAYER_1 ? player1.get() : player2.get();
}

Player* GameModeManager::defender() const {
    return currentTurn == TurnOwner::PLAYER_1 ? player2.get() : player1.get();
}

void GameModeManager::setupMatch(GameMode mode, PlayerProfile* p1, PlayerProfile* p2, BotDifficulty difficulty) {
    currentMode = mode;
    player1 = make_unique<HumanPlayer>(p1);
    if (mode == GameMode::PVE) {
        if (difficulty == BotDifficulty::EASY) player2 = make_unique<EasyBotPlayer>(p2);
        else                                   player2 = make_unique<SmartBotPlayer>(p2);
    }
    else {
        player2 = make_unique<HumanPlayer>(p2);
    }

    roundNumber = 1;
    turnCounter = 0;
    isGameActive = true;
    currentTurn = TurnOwner::PLAYER_1;

    cout << "\n[GameModeManager]: Ініціалізовано матч у режимі "
        << (mode == GameMode::PVE ? "PvE (проти ШІ)" : "PvP (2 гравці)") << "!\n";
    player1->printInfo();
    player2->printInfo();
}

bool GameModeManager::executeNextTurn() {
    if (!isGameActive || !player1 || !player2) return true;

    if (++turnCounter > MAX_TURNS) {
        cout << "\n[GameModeManager]: Досягнуто ліміт ходів (" << MAX_TURNS << "). НІЧИЯ.\n";
        isGameActive = false;
        return true;
    }

    Player* atk = attacker();
    Player* def = defender();
    int playerId = (currentTurn == TurnOwner::PLAYER_1) ? 1 : 2;

    TurnDecision decision = atk->makeTurnDecision(&defaultArtillery);
    if (decision.attack == nullptr) decision.attack = &defaultArtillery;

    ShotResult res = combat.executeAttack(playerId, decision.attack,
        def->getField(), &atk->getField(),
        decision.x, decision.y);

    atk->onShotFeedback(decision.x, decision.y, res);

    if (def->getField().areAllShipsDestroyed()) {
        finishMatch(atk, def);
        return true;
    }
    if (atk->getField().areAllShipsDestroyed()) {
        finishMatch(def, atk);
        return true;
    }

    if (res == ShotResult::MISS || res == ShotResult::MINE_TRIGGERED) {
        def->getField().updateMovingShips(); // поліморфне зміщення рухомих катерів
        if (currentTurn == TurnOwner::PLAYER_1) {
            currentTurn = TurnOwner::PLAYER_2;
        }
        else {
            currentTurn = TurnOwner::PLAYER_1;
            roundNumber++;
        }
    }
    return false;
}

void GameModeManager::finishMatch(Player* winner, Player* loser) {
    cout << "\n*********************************************************\n";
    cout << " ПЕРЕМОГА! Усі кораблі противника повністю знищено!\n";
    cout << " Переможець матчу: " << winner->getName() << " [" << winner->getPlayerType() << "]\n";
    cout << "*********************************************************\n";
    if (winner->getProfile()) winner->getProfile()->recordWin();
    if (loser->getProfile())  loser->getProfile()->recordLoss();
    isGameActive = false;
}

string GameModeManager::getCurrentPlayerName() const {
    Player* p = attacker();
    return p ? p->getName() : "Невідомий";
}

bool GameModeManager::isMatchActive() const { return isGameActive; }
GameMode GameModeManager::getGameMode() const { return currentMode; }
TurnOwner GameModeManager::getCurrentTurn() const { return currentTurn; }
int GameModeManager::getTurnNumber() const { return roundNumber; }

void GameModeManager::printStatus() const {
    string modeStr = (currentMode == GameMode::PVE) ? "PvE (проти ШІ)" :
        (currentMode == GameMode::PVP) ? "PvP (2 гравці)" : "Не обрано";
    cout << "----------------------------------------\n"
        << "Статус гри: " << (isGameActive ? "Активна" : "Неактивна") << "\n"
        << "Режим: " << modeStr << " | Раунд: " << roundNumber << " | Ходів: " << turnCounter << "\n"
        << "Поточний хід: " << getCurrentPlayerName();
    if (Player* p = attacker()) cout << " [" << p->getPlayerType() << "]";
    cout << "\n----------------------------------------\n";
}
