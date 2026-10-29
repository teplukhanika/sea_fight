#pragma once
#include <string>
#include <iostream>
#include "PlayerProfile.h"
#include "FieldManager.h"
#include "CombatManager.h"
#include "MapLayer.h"
#include <utility>
#include "BotAI.h"
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
    PlayerProfile* player1;
    PlayerProfile* player2;
    FieldManager field1;
    FieldManager field2;
    CombatManager combat;
    BotAI bot;
    int roundNumber;
    bool isGameActive;

public:
    GameModeManager()
        : currentMode(GameMode::NOT_SELECTED), currentTurn(TurnOwner::PLAYER_1),
        player1(nullptr), player2(nullptr), roundNumber(1), isGameActive(false) {
        combat.bindFields(&field1, &field2);
    }
    FieldManager& getField1() { return field1; }
    FieldManager& getField2() { return field2; }
    CombatManager& getCombat() { return combat; }

    void setupMatch(GameMode mode, PlayerProfile* p1, PlayerProfile* p2 = nullptr);
    bool playTurn(int targetX, int targetY, MapLayer layer = MapLayer::WATER);

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