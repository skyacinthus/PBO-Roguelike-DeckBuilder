#ifndef GAME_H
#define GAME_H
#include "room.h"
#include "player.h"
#include <memory>
#include <vector>
using namespace std; 

class Game {
private:
    Player player;
    int roomsCleared;
    int eliteCount;

    vector<unique_ptr<Room>> generateRoomChoices(int roomNumber);
    int askPlayerToChoose(const vector<unique_ptr<Room>>& choices);
    void showEndScreen(bool won);

public:
    Game();
    void run();
};

#endif