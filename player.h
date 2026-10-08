#pragma once
#include "character.h"

class Player : public Character {
private:
    int energy;
    int maxEnergy;
    int drawPerTurn;

public:
    Player(const string& name, int maxHp, int maxEnergy = 3, int drawPerTurn = 5);

    void startTurn() override;   // reset block, isi energi, tarik kartu
    void endTurn();              // buang sisa kartu, kurangi efek (weak, dll.)

    bool playCard(int handIndex, Character& target);

    void startBattle();          // siapkan deck untuk pertarungan baru

    bool spendEnergy(int cost);
    int getEnergy() const { return energy; }
    int getMaxEnergy() const { return maxEnergy; }
};