#ifndef PLAYER_H
#define PLAYER_H
#include "character.h"

class Player : public Character {
private:
    int energy;
    int maxEnergy;
    int drawPerTurn;

public:
    Player(const string& name, int maxHp, int maxEnergy = 3, int drawPerTurn = 5);

    void startTurn() override;   
    void endTurn();              

    bool playCard(int handIndex, Character& target);

    void startBattle();

    bool spendEnergy(int cost);
    int getEnergy() const { return energy; }
    int getMaxEnergy() const { return maxEnergy; }
};
#endif PLAYER_H