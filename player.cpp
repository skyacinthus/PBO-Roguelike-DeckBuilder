#include "player.h"
using namespace std;

Player::Player(const string& name, int maxHp, int maxEnergy, int drawPerTurn) : Character(name, maxHp), energy(maxEnergy), maxEnergy(maxEnergy), drawPerTurn(drawPerTurn) {}

void Player::startTurn() {
    clearBlock();        // block reset tiap awal giliran (boleh, karena protected)
    energy = maxEnergy;  // energi penuh lagi
}
void Player::startBattle() {
    resetBattleState();

}
void Player::startTurn() {
    clearBlock();
    energy = maxEnergy;
}

void Player::endTurn() {
    endTurnEffects();
}

bool Player::spendEnergy(int cost) {
    if (cost < 0 || cost > energy) return false;
    energy -= cost;
    return true;
}