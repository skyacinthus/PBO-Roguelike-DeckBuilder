#include "deck.h"
#include <algorithm>
using namespace std;

Deck::Deck() : rng(random_device{}()) {}

void Deck::shuffleDrawPile() {
    shuffle(drawPile.begin(), drawPile.end(), rng);
}

void Deck::reshuffleDiscardIntoDraw() {
    for (auto& c : discardPile)
        drawPile.push_back(std::move(c));
    discardPile.clear();
    shuffleDrawPile();
}

void Deck::addCard(unique_ptr<Card> card) {
    drawPile.push_back(std::move(card));
}

void Deck::startBattle() {
    for (auto& c : hand)        drawPile.push_back(std::move(c));
    for (auto& c : discardPile) drawPile.push_back(std::move(c));
    hand.clear();
    discardPile.clear();
    shuffleDrawPile();
}

void Deck::draw(int n) {
    for (int i = 0; i < n; i++) {
        if (drawPile.empty()) {
            if (discardPile.empty()) break;
            reshuffleDiscardIntoDraw();
        }
        hand.push_back(std::move(drawPile.back()));
        drawPile.pop_back();
    }
}

void Deck::discardFromHand(int index) {
    if (index < 0 || index >= (int)hand.size()) return;
    discardPile.push_back(std::move(hand[index]));
    hand.erase(hand.begin() + index);
}

void Deck::discardHand() {
    for (auto& c : hand)
        discardPile.push_back(std::move(c));
    hand.clear();
}