#ifndef PLAYER_H
#define PLAYER_H
#include "character.h"
#include "deck.h"
#include <memory>
#include <string>
using namespace std;

class Player : public Character {
private:
    int energy;
    int maxEnergy;
    int drawPerTurn;
    Deck deck;

public:
    Player();
    Player(const string& name, int maxHp, int maxEnergy = 3, int drawPerTurn = 5);

    
    void startBattle();
    void startTurn() override;   
    void endTurn();              

    bool playCard(int handIndex, Character& target); // ini emang blm ada implementasinya kah? 
    //barusan ku add
    void addCardToDeck(std::unique_ptr<Card> card);
    
    bool spendEnergy(int cost);
    void addEnergy(int amount);
    int getEnergy() const { return energy; }
    int getMaxEnergy() const { return maxEnergy; }
    int getDrawPerTurn() const { return drawPerTurn; }
    Deck& getDeck() { return deck; }
    const Deck& getDeck() const { return deck; }
};
#endif PLAYER_H