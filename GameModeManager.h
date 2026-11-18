#pragma once
#include <string>
#include <memory>
#include "Player.h"
#include "CombatManager.h"
#include "AttackAction.h"
#include "PlayerProfile.h"
using namespace std;

enum class GameMode { NOT_SELECTED, PVE, PVP };
enum class BotDifficulty { EASY, SMART };
enum class TurnOwner { PLAYER_1, PLAYER_2 };

class GameModeManager {
private:
    GameMode currentMode;
    TurnOwner currentTurn;
    unique_ptr<Player> player1;        // КОМПОЗИЦІЯ: менеджер створює і знищує гравців
    unique_ptr<Player> player2;
    CombatManager combat;              // КОМПОЗИЦІЯ: бойова система матчу
    SingleShotAttack defaultArtillery; // стандартна атака, якщо гравець не обрав іншу
    int roundNumber;
    int turnCounter;
    bool isGameActive;

    static const int MAX_TURNS = 500;  // захист від нескінченного матчу

    Player* attacker() const;
    Player* defender() const;
    void finishMatch(Player* winner, Player* loser);

public:
    GameModeManager();

    GameModeManager(const GameModeManager&) = delete;
    GameModeManager& operator=(const GameModeManager&) = delete;

    void setupMatch(GameMode mode, PlayerProfile* p1, PlayerProfile* p2 = nullptr,
        BotDifficulty difficulty = BotDifficulty::SMART);

    bool executeNextTurn();

    Player* getPlayer1() const { return player1.get(); }
    Player* getPlayer2() const { return player2.get(); }
    CombatManager& getCombat() { return combat; }

    string getCurrentPlayerName() const;
    bool isMatchActive() const;
    GameMode getGameMode() const;
    TurnOwner getCurrentTurn() const;
    int getTurnNumber() const;
    void printStatus() const;
};
