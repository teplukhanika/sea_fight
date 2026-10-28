#pragma once
#include <vector>
#include <utility>
#include <iostream>
#include "CombatManager.h"
using namespace std;

class BotAI {
private:
    vector<pair<int, int>> huntGrid;      // КОМПОЗИЦІЯ: основна сітка пошуку
    vector<pair<int, int>> priorityQueue; // КОМПОЗИЦІЯ: черга сусідніх клітинок для добивання пораненого корабля
    bool visited[10][10];

public:
    BotAI() {
        reset();
    }

    void reset() {
        huntGrid.clear();
        priorityQueue.clear();
        for (int y = 0; y < 10; y++) {
            for (int x = 0; x < 10; x++) {
                visited[y][x] = false;
                huntGrid.push_back({ x, y });
            }
        }
    }
    pair<int, int> makeMove();
    void notifyShotResult(int x, int y, ShotResult result);
};