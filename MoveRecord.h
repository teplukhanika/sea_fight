#pragma once
#include <string>
#include "MapLayer.h"

using namespace std;

enum class ShotResult { MISS, HIT, DESTROYED, MINE_TRIGGERED, INVALID };

class MoveRecord {
private:
    int turnNum;
    int playerId;
    int x, y;
    MapLayer layer;
    ShotResult result;
    string details;

public:
    MoveRecord(int turn, int player, int tx, int ty, MapLayer l, ShotResult res, const string& info = "");
    ShotResult getResult() const;
    int getPlayerId() const;
    string toString() const;
};