#pragma once
#include <string>
#include "BotAI.h"
#include "CombatManager.h"
#include "FieldManager.h"
#include "PlayerProfile.h"
using namespace std;

enum class GameMode { NOT_SELECTED, PVE, PVP };
enum class TurnOwner { PLAYER_1, PLAYER_2, AI_BOT };

class GameModeManager {
private:
    GameMode currentMode;
    TurnOwner currentTurn;
    PlayerProfile* player1;    // АГРЕГАЦІЯ: профіль гравця 1
    PlayerProfile* player2;    // АГРЕГАЦІЯ: профіль гравця 2
    FieldManager field1;       // КОМПОЗИЦІЯ: поле гравця 1
    FieldManager field2;       // КОМПОЗИЦІЯ: поле гравця 2 / Бота
    CombatManager combat;      // КОМПОЗИЦІЯ: бойова система матчу
    BotAI bot;                 // КОМПОЗИЦІЯ: ШІ-бот
    int roundNumber;
    bool isGameActive;

public:
    GameModeManager();

    GameModeManager(const GameModeManager&) = delete;
    GameModeManager& operator=(const GameModeManager&) = delete;

    FieldManager& getField1() { return field1; }
    FieldManager& getField2() { return field2; }
    CombatManager& getCombat() { return combat; }

    void setupMatch(GameMode mode, PlayerProfile* p1, PlayerProfile* p2 = nullptr);
    bool playTurn(int targetX, int targetY, MapLayer layer = MapLayer::WATER);

    string getCurrentPlayerName() const;
    bool isMatchActive() const;
    GameMode getGameMode() const;
    TurnOwner getCurrentTurn() const;
    int getTurnNumber() const;
    void printStatus() const;
};
