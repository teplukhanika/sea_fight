#pragma once
#include <string>
#include <iostream>
using namespace std;
enum class GameMode {
    NOT_SELECTED,
    PVE,
    PVP 
};

enum class TurnOwner {
    PLAYER_1,
    PLAYER_2,
    AI_BOT
};

class GameModeManager {
private:
    GameMode currentMode;
    TurnOwner currentTurn;
    string player1Name;
    string player2Name;
    int turnNumber;
    bool isGameActive;

public:
    GameModeManager();

    void selectGameMode(GameMode mode, const string& p1Name, const string& p2Name = "AI_Bot");

    void startMatch();

    void switchTurn(bool hitSuccess = false);

    void endMatch();

    GameMode getGameMode() const;
    TurnOwner getCurrentTurn() const;
    string getCurrentPlayerName() const;
    int getTurnNumber() const;
    bool isMatchActive() const;
    void printStatus() const;
};