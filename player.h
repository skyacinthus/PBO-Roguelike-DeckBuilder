#ifndef PLAYER_H
#define PLAYER_H
#include "character.h"
#include <string>
using namespace std;

class Player : public Character {
private:
    int energy;
    int maxEnergy;
    int drawPerTurn;

public:
    Player();
    Player(const string& name, int maxHp, int maxEnergy = 3, int drawPerTurn = 5);

    void startTurn() override;   
    void endTurn();              

    bool playCard(int handIndex, Character& target); // ini emang blm ada implementasinya kah? 

    void startBattle();

    bool spendEnergy(int cost);
    void addEnergy(int amount);
    int getEnergy() const { return energy; }
    int getMaxEnergy() const { return maxEnergy; }
};
#endif PLAYER_H