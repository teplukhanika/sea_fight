#include "MoveRecord.h"

MoveRecord::MoveRecord()
    : x(-1), y(-1), result(ShotResult::INVALID), playerId(0) {
}

MoveRecord::MoveRecord(int targetX, int targetY, ShotResult res, int player)
    : x(targetX), y(targetY), result(res), playerId(player) {
}

int MoveRecord::getX() const { return x; }
int MoveRecord::getY() const { return y; }
ShotResult MoveRecord::getResult() const { return result; }
int MoveRecord::getPlayerId() const { return playerId; }

string MoveRecord::toString() const {
    string resStr;
    switch (result) {
    case ShotResult::MISS: resStr = "Промах"; break;
    case ShotResult::HIT: resStr = "Влучання"; break;
    case ShotResult::DESTROYED: resStr = "Корабель знищено"; break;
    case ShotResult::INVALID: resStr = "Помилка"; break;
    }
    return "Гравець " + to_string(playerId) + " -> (" + to_string(x) + ", " + to_string(y) + ") : " + resStr;
}