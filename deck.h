#ifndef DECK_H
#define DECK_H

#include "card.h"
#include <vector>
#include <memory>
#include <random>
using namespace std;

class Deck {
private:
    vector<unique_ptr<Card>> drawPile;
    vector<unique_ptr<Card>> hand;
    vector<unique_ptr<Card>> discardPile;
    mt19937 rng;

    void shuffleDrawPile();
    void reshuffleDiscardIntoDraw();

public:
    Deck();

    void addCard(unique_ptr<Card> card);
    void startBattle();
    void draw(int n);
    void discardFromHand(int index);
    void discardHand();

    int handSize() const { return (int)hand.size(); }
    int drawPileSize() const { return (int)drawPile.size(); }
    int discardPileSize() const { return (int)discardPile.size(); }
    int totalCards() const { return (int)(drawPile.size() + hand.size() + discardPile.size()); }

    Card& cardInHand(int index) { return *hand[index]; }
    const Card& cardInHand(int index) const { return *hand[index]; }
};

#endif 