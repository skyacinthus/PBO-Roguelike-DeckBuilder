#include "enemy.h"
using namespace std;

Enemy::Enemy(const string& name, int maxHp, EnemyTier tier) : 
    Character(name, maxHp), tier(tier), nextIntent{IntentType::ATTACK, 0, 0} {};// buat hapus garbage val

void Enemy::startTurn() {
    clearBlock();
}

void Enemy::executeIntent(Character& target){
    switch (nextIntent.type) {
        case IntentType::ATTACK:{ 
            int damage = getAttackPower(nextIntent.value);
            target.takeDamage(damage);
            break;
        }   
        case IntentType::DEFEND:
            addBlock(nextIntent.value);
            break;
        case IntentType::BUFF:
            addStrength(nextIntent.value);
            break;
        case IntentType::DEBUFF:
            target.applyWeak(nextIntent.turns);
            break;
    }
}
