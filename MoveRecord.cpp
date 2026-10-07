#include "MoveRecord.h"

MoveRecord::MoveRecord(int targetX, int targetY, ShotResult res, int player)
    : x(targetX), y(targetY), result(res), playerId(player) {
}

int MoveRecord::getX() const { return x; }
int MoveRecord::getY() const { return y; }
ShotResult MoveRecord::getResult() const { return result; }
int MoveRecord::getPlayerId() const { return playerId; }

std::string MoveRecord::toString() const {
    std::string resStr;
    switch (result) {
    case ShotResult::MISS: resStr = "Промах"; break;
    case ShotResult::HIT: resStr = "Влучання"; break;
    case ShotResult::DESTROYED: resStr = "Корабель знищено"; break;
    case ShotResult::INVALID: resStr = "Помилка"; break;
    }
    return "Гравець " + std::to_string(playerId) + " -> (" + std::to_string(x) + ", " + std::to_string(y) + ") : " + resStr;
}