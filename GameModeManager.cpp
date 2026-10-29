#include "GameModeManager.h"
#include <iostream>

using namespace std;


void GameModeManager::setupMatch(GameMode mode, PlayerProfile* p1, PlayerProfile* p2) {
    currentMode = mode;
    player1 = p1;
    player2 = p2;
    field1.clearField();
    field2.clearField();
    bot.reset();
    roundNumber = 1;
    isGameActive = true;
    currentTurn = TurnOwner::PLAYER_1;

    cout << "\n[GameModeManager]: Ініціалізовано матч у режимі "
        << (mode == GameMode::PVE ? "PvE (проти ШІ)" : "PvP (2 гравці)") << "!\n";
}
string GameModeManager::getCurrentPlayerName() const {
    if (currentTurn == TurnOwner::PLAYER_1 && player1) return player1->getName();
    if (currentTurn == TurnOwner::PLAYER_2 && player2) return player2->getName();
    return "ШІ-Флагман (Бот)";
}

bool GameModeManager::playTurn(int targetX, int targetY, MapLayer layer) {
    if (!isGameActive) return false;

    FieldManager& targetField = (currentTurn == TurnOwner::PLAYER_1) ? field2 : field1;
    PlayerProfile* activeProfile = (currentTurn == TurnOwner::PLAYER_1) ? player1 : player2;

    if (currentTurn == TurnOwner::AI_BOT) {
        pair<int, int> botCoords = bot.makeMove();
        targetX = botCoords.first;
        targetY = botCoords.second;
    }

    ShotResult res = combat.processShot(targetField, targetX, targetY, layer);

    if (currentTurn == TurnOwner::AI_BOT) {
        bot.notifyShotResult(targetX, targetY, res);
    }

    if (res == ShotResult::DESTROYED && activeProfile != nullptr) {
        activeProfile->addDestroyedShipKill();
    }

    if (targetField.areAllShipsDestroyed()) {
        cout << "\n********************************************************\n";
        cout << " ПЕРЕМОГА! Усі кораблі противника повністю знищено!\n";
        cout << " Переможець матчу: " << getCurrentPlayerName() << "\n";
        cout << "********************************************************\n";
        if (currentTurn == TurnOwner::PLAYER_1) {
            if (player1) player1->recordWin();
            if (player2) player2->recordLoss();
        }
        else {
            if (player2) player2->recordWin();
            if (player1) player1->recordLoss();
        }
        isGameActive = false;
        return true;
    }

    if (res == ShotResult::MISS || res == ShotResult::MINE_TRIGGERED) {
        if (currentTurn == TurnOwner::PLAYER_1) {
            currentTurn = (currentMode == GameMode::PVE) ? TurnOwner::AI_BOT : TurnOwner::PLAYER_2;
        }
        else {
            currentTurn = TurnOwner::PLAYER_1;
            roundNumber++;
        }
    }
    return false;
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
        << "Режим: " << modeStr << " | Раунд: " << roundNumber << "\n"
        << "Поточний хід: " << getCurrentPlayerName() << "\n"
        << "----------------------------------------\n";
}