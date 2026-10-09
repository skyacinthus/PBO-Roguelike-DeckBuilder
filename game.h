#ifndef GAME_H
#define GAME_H

#include <memory>
#include <vector>
#include "player.h"
#include "room.h"

class Game {
private:
    Player player;
    int roomsCleared;
    int treasureCount;          // treasure rooms the player has taken this run

    std::vector<std::unique_ptr<Room>> generateRoomChoices(int roomNumber);
    void showEndScreen(bool won);

public:
    Game();
    void run();
};

#endif // GAME_H