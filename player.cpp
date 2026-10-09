#include "player.h"
using namespace std;

Player::Player() : Player("Mahasiswa", 80, 3, 5) {}

Player::Player(const string& name, int maxHp, int maxEnergy, int drawPerTurn) : Character(name, maxHp), energy(maxEnergy), maxEnergy(maxEnergy), drawPerTurn(drawPerTurn) {}

void Player::startTurn() {
    clearBlock();        
    energy = maxEnergy; 
}
void Player::startBattle() {
    resetBattleState();

}
void Player::endTurn() {
    endTurnEffects();
}

bool Player::spendEnergy(int cost) {
    if (cost < 0 || cost > energy) return false;
    energy -= cost;
    return true;
}
void Player::addEnergy(int amount) {
    if (amount > 0) energy += amount;
}
