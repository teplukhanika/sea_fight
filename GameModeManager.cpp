#include "GameModeManager.h"
#include <iostream>

using namespace std;

GameModeManager::GameModeManager()
    : currentMode(GameMode::NOT_SELECTED),
    currentTurn(TurnOwner::PLAYER_1),
    player1Name("None"),
    player2Name("None"),
    turnNumber(0),
    isGameActive(false) {
}

void GameModeManager::selectGameMode(GameMode mode, const string& p1Name, const string& p2Name) {
    currentMode = mode;
    player1Name = p1Name;

    if (mode == GameMode::PVE) {
        player2Name = "ШІ (Бот)";
        cout << "GameModeManager: Обрано режим: PvE (Гра з ботом).\n";
    }
    else if (mode == GameMode::PVP) {
        player2Name = p2Name;
        cout << "GameModeManager: Обрано режим: PvP (Мультиплеєр).\n";
    }
    cout << "GameModeManager: Учасники: " << player1Name << " проти " << player2Name << "\n";
}

void GameModeManager::startMatch() {
    if (currentMode == GameMode::NOT_SELECTED) {
        cout << "Помилка: Неможливо почати гру: режим не обрано!\n";
        return;
    }
    isGameActive = true;
    turnNumber = 1;
    currentTurn = TurnOwner::PLAYER_1;
    cout << "GameModeManager: Матч розпочато! Хід №" << turnNumber
        << ". Першим ходить: " << getCurrentPlayerName() << "\n";
}

void GameModeManager::switchTurn(bool hitSuccess) {
    if (!isGameActive) {
        cout << "Помилка: Гра не активна!\n";
        return;
    }

    if (hitSuccess) {
        cout << "GameModeManager: Влучання! " << getCurrentPlayerName()
            << " отримує додатковий хід.\n";
        return;
    }

    if (currentTurn == TurnOwner::PLAYER_1) {
        currentTurn = (currentMode == GameMode::PVE) ? TurnOwner::AI_BOT : TurnOwner::PLAYER_2;
    }
    else {
        currentTurn = TurnOwner::PLAYER_1;
        turnNumber++;
    }

    cout << "GameModeManager: Перехід ходу (Раунд " << turnNumber << "). Тепер ходить: "
        << getCurrentPlayerName() << "\n";
}

void GameModeManager::endMatch() {
    if (!isGameActive) return;
    isGameActive = false;
    cout << "GameModeManager: Матч завершено на раунді " << turnNumber
        << "! Переможець за останнім ходом: " << getCurrentPlayerName() << "\n";
}

GameMode GameModeManager::getGameMode() const { return currentMode; }
TurnOwner GameModeManager::getCurrentTurn() const { return currentTurn; }
int GameModeManager::getTurnNumber() const { return turnNumber; }
bool GameModeManager::isMatchActive() const { return isGameActive; }

string GameModeManager::getCurrentPlayerName() const {
    if (currentTurn == TurnOwner::PLAYER_1) return player1Name;
    return player2Name;
}

void GameModeManager::printStatus() const {
    string modeStr = (currentMode == GameMode::PVE) ? "PvE (проти ШІ)" :
        (currentMode == GameMode::PVP) ? "PvP (2 гравці)" : "Не обрано";
    cout << "----------------------------------------\n"
        << "Статус гри: " << (isGameActive ? "Активна" : "Неактивна") << "\n"
        << "Режим: " << modeStr << " | Раунд: " << turnNumber << "\n"
        << "Поточний хід: " << getCurrentPlayerName() << "\n"
        << "----------------------------------------\n";
}