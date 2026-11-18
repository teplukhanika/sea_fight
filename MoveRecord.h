#pragma once
#include <string>

using namespace std;

enum class ShotResult { MISS, HIT, DESTROYED, MINE_TRIGGERED };

class MoveRecord {
private:
    int turnId;
    int playerId;
    int x, y;
    string attackType;
    ShotResult result;

public:
    MoveRecord(int t, int p, int tx, int ty, const string& atk, ShotResult res);
    ShotResult getResult() const;
    int getPlayerId() const;
    string toString() const;
};