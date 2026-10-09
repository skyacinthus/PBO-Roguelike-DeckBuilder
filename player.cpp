#include "player.h"
#include "card.h"
#include <iostream>
using namespace std;

Player::Player() : Player("Mahasiswa", 80, 3, 5) {}

Player::Player(const string& name, int maxHp, int maxEnergy, int drawPerTurn)
    : Character(name, maxHp),
      energy(maxEnergy),
      maxEnergy(maxEnergy),
      drawPerTurn(drawPerTurn) {
    // Isi deck dengan kartu awal
    for (auto& c : createStarterDeck())
        deck.addCard(std::move(c));
}
void Player::startBattle() {
    resetBattleState();
    energy = maxEnergy;
    deck.startBattle();

}
void Player::startTurn() {
    clearBlock();        
    energy = maxEnergy; 
    deck.draw(drawPerTurn);
}

void Player::endTurn() {
    deck.discardHand();
    endTurnEffects();
}

bool Player::playCard(int handIndex, Character& target) {
    if (handIndex < 0 || handIndex >= deck.handSize()) return false;
 
    Card& card = deck.cardInHand(handIndex);
    if (!spendEnergy(card.getCost())) return false;
 
    card.play(*this, target);
    deck.discardFromHand(handIndex);
    return true;
}

void Player::addCardToDeck(unique_ptr<Card> card) {
    if (card) deck.addCard(std::move(card));
}

bool Player::spendEnergy(int cost) {
    if (cost < 0 || cost > energy) return false;
    energy -= cost;
    return true;
}
void Player::addEnergy(int amount) {
    if (amount > 0) energy += amount;
}

void Player::printHand() const {
    int handSize = deck.handSize();
    
    if (handSize == 0) {
        cout << "[ Tangan Kosong ]\n";
        return;
    }

    cout << "\n=== Kartu di Tangan (Energy: " << energy << "/" << maxEnergy << ") ===\n";
    cout << "[0] Selesaikan Turn\n"; 
    for (int i = 0; i < handSize; ++i) {
        const Card& card = deck.cardInHand(i);
        cout << "[" << (i + 1) << "] " << card.getName() 
             << " (Cost: " << card.getCost() << " Energi)"
             << " - " << card.getDescription() << "\n";
    }
    cout << "========================================================\n";
}