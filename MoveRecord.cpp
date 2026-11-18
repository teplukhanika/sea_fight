#include "MoveRecord.h"

MoveRecord::MoveRecord(int t, int p, int tx, int ty, const string& atk, ShotResult res)
    : turnId(t), playerId(p), x(tx), y(ty), attackType(atk), result(res) {
}

ShotResult MoveRecord::getResult() const {
    return result;
}

int MoveRecord::getPlayerId() const {
    return playerId;
}

string MoveRecord::toString() const {
    string r = (result == ShotResult::DESTROYED) ? "ЗНИЩЕНО" :
        (result == ShotResult::HIT) ? "Влучання" :
        (result == ShotResult::MINE_TRIGGERED) ? "Міна!" : "Промах";
    return "[Хід " + to_string(turnId) + "] Гр." + to_string(playerId) + " [" + attackType + "] -> (" +
        to_string(x) + "," + to_string(y) + ") : " + r;
}