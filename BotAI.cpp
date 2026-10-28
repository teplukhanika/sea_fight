#include "BotAI.h"
using namespace std;
pair<int, int> BotAI::makeMove() {
    while (!priorityQueue.empty()) {
        pair<int, int> target = priorityQueue.back();
        priorityQueue.pop_back();
        if (target.first >= 0 && target.first < 10 && target.second >= 0 && target.second < 10 &&
            !visited[target.second][target.first]) {
            visited[target.second][target.first] = true;
            cout << "[BotAI (Режим добивання)]: Стріляє у сусідню клітинку ("
                << target.first << ", " << target.second << ")\n";
            return target;
        }
    }

    while (!huntGrid.empty()) {
        pair<int, int> target = huntGrid.front();
        huntGrid.erase(huntGrid.begin());
        if (!visited[target.second][target.first]) {
            visited[target.second][target.first] = true;
            cout << "[BotAI (Режим розвідки)]: Стріляє у (" << target.first << ", " << target.second << ")\n";
            return target;
        }
    }
    return { 0, 0 };
}
void BotAI::notifyShotResult(int x, int y, ShotResult result) {
    if (result == ShotResult::HIT) {
        priorityQueue.push_back({ x + 1, y });
        priorityQueue.push_back({ x - 1, y });
        priorityQueue.push_back({ x, y + 1 });
        priorityQueue.push_back({ x, y - 1 });
    }
    else if (result == ShotResult::DESTROYED) {
        priorityQueue.clear(); // Корабель знищено, очищаємо чергу добивання
    }
}

