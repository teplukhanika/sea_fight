#pragma once
#include <string>
#include <iostream>

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
    std::string player1Name;
    std::string player2Name;
    int turnNumber;
    bool isGameActive;

public:
    GameModeManager();

    void selectGameMode(GameMode mode, const std::string& p1Name, const std::string& p2Name = "AI_Bot");

    void startMatch();

    void switchTurn(bool hitSuccess = false);

    void endMatch();

    GameMode getGameMode() const;
    TurnOwner getCurrentTurn() const;
    std::string getCurrentPlayerName() const;
    int getTurnNumber() const;
    bool isMatchActive() const;
    void printStatus() const;
};