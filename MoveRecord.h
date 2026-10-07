#pragma once
#include <string>

enum class ShotResult { MISS, HIT, DESTROYED, INVALID };

class MoveRecord {
private:
    int x;
    int y;
    ShotResult result;
    int playerId;

public:
    MoveRecord(int targetX, int targetY, ShotResult res, int player);

    int getX() const;
    int getY() const;
    ShotResult getResult() const;
    int getPlayerId() const;

    std::string toString() const;
};