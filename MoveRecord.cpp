#include "MoveRecord.h"

MoveRecord::MoveRecord(int turn, int player, int tx, int ty, MapLayer l, ShotResult res, const string& info)
    : turnNum(turn), playerId(player), x(tx), y(ty), layer(l), result(res), details(info) {
}

ShotResult MoveRecord::getResult() const { return result; }
int MoveRecord::getPlayerId() const { return playerId; }

string MoveRecord::toString() const {
    string resStr;
    switch (result) {
    case ShotResult::MISS:           resStr = "Промах"; break;
    case ShotResult::HIT:            resStr = "Поранено"; break;
    case ShotResult::DESTROYED:      resStr = "Знищено (" + details + ")"; break;
    case ShotResult::MINE_TRIGGERED: resStr = "Підрив міни"; break;
    case ShotResult::INVALID:        resStr = "Повтор/Помилка"; break;
    }
    return "Хід " + to_string(turnNum) + " Гравець " + to_string(playerId) +
        " -> (" + to_string(x) + "," + to_string(y) + ", шар " +
        to_string(static_cast<int>(layer)) + ") : " + resStr;
}