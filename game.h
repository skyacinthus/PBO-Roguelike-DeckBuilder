#ifndef GAME_H
#define GAME_H
#include "room.h"
#include "player.h"
#include <memory>
using namespace std; 


unique_ptr<Room> generateRandomRoom(int currentFloor);
unique_ptr<Room> chooseNextRoom(int currentFloor);
void runGame(Player& player);

#endif