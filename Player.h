#pragma once
#include <string>
#include <vector>
#include <random>
#include "FieldManager.h"
#include "PlayerProfile.h"
#include "CombatManager.h"
#include "AttackAction.h"
#include "BotAI.h"
using namespace std;

struct TurnDecision {
    int x;
    int y;
    AttackAction* attack;
};

class Player {
protected:
    PlayerProfile* profile;   // АГРЕГАЦІЯ: профіль живе в RegistrationManager
    FieldManager ownField;    // КОМПОЗИЦІЯ: власне поле гравця

public:
    explicit Player(PlayerProfile* prof);
    virtual ~Player();

    Player(const Player&) = delete;
    Player& operator=(const Player&) = delete;

    string getName() const;
    PlayerProfile* getProfile() const;
    FieldManager& getField();
    const FieldManager& getField() const;

    virtual TurnDecision makeTurnDecision(AttackAction* defaultAttack) = 0; // чисто віртуальний
    virtual void onShotFeedback(int x, int y, ShotResult result);          // реакція на результат пострілу
    virtual string getPlayerType() const = 0;                              // назва типу гравця
    virtual bool isBot() const;
    virtual void reset();                                                  // скидання стану перед новим матчем
    void printInfo() const;
};

class HumanPlayer : public Player {
private:
    vector<pair<int, int>> scriptedCoords;   // заплановані ходи (для демонстрації)
    vector<AttackAction*> scriptedAttacks;
    size_t stepIndex;
    bool interactive;                        // чи можна питати координати з клавіатури
    bool shotMap[10][10];                    // куди вже стріляв (для запасного режиму)

    TurnDecision askFromConsole(AttackAction* defaultAttack);
    TurnDecision fallbackNextCell(AttackAction* defaultAttack);

public:
    explicit HumanPlayer(PlayerProfile* prof, bool allowConsoleInput = true);

    void queuePlannedMove(int x, int y, AttackAction* customAttack = nullptr);
    bool hasPlannedMoves() const;

    TurnDecision makeTurnDecision(AttackAction* defaultAttack) override;
    string getPlayerType() const override { return "Людина"; }
    void reset() override;
};

class EasyBotPlayer : public Player {
private:
    vector<pair<int, int>> freeCells;
    mt19937 rng;

public:
    explicit EasyBotPlayer(PlayerProfile* prof, unsigned int seed = random_device{}());

    TurnDecision makeTurnDecision(AttackAction* defaultAttack) override;
    string getPlayerType() const override { return "Бот (легкий)"; }
    bool isBot() const override { return true; }
    void reset() override;
};

class SmartBotPlayer : public Player {
private:
    BotAI brain; // КОМПОЗИЦІЯ: "мозок" бота з чергою добивання

public:
    explicit SmartBotPlayer(PlayerProfile* prof);

    TurnDecision makeTurnDecision(AttackAction* defaultAttack) override;
    void onShotFeedback(int x, int y, ShotResult result) override;
    string getPlayerType() const override { return "Бот (розумний)"; }
    bool isBot() const override { return true; }
    void reset() override;
};
