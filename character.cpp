#include "character.h"
#include <algorithm> 
using namespace std;

Character::Character(const string& name, int maxHp)
    : name(name), hp(maxHp), maxHp(maxHp), block(0), strength(0), weak(0) {}

void Character::clearBlock() {
    block = 0;
}

int Character::takeDamage(int amount) {
    if (amount < 0) amount = 0;

    int absorbed = min(block, amount);
    block -= absorbed;
    int remaining = amount - absorbed;

    int hpLost = min(hp, remaining);
    hp -= hpLost;
    return hpLost;
}

void Character::loseHP(int amount) {
    if (amount < 0) amount = 0;
    hp = max(0, hp - amount);
}

void Character::heal(int amount) {
    if (amount < 0) amount = 0;
    hp = min(maxHp, hp + amount);
}

void Character::addBlock(int amount) {
    if (amount > 0) block += amount;
}

void Character::addStrength(int amount) {
    strength += amount;
}

void Character::applyWeak(int turns) {
    if (turns > 0) weak += turns;
}

int Character::getAttackPower(int baseDamage) const {
    int total = baseDamage + strength;
    if (weak > 0) total = total * 3 / 4;
    return max(0, total);
}

void Character::endTurnEffects() {
    if (weak > 0) weak--;
}

void Character::resetBattleState() {
    block = 0;
    strength = 0;
    weak = 0;
}

bool Character::isAlive() const {
    return hp > 0;
}