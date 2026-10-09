#include "enemy.h"
#include <string>
#include <iostream>
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
            int lost = target.takeDamage(damage);
            cout << getName() << " menyerang! " 
                 << target.getName() << " kehilangan " << lost << " HP.\n";
            break;
            break;
        }   
        case IntentType::DEFEND:
            addBlock(nextIntent.value);
            cout << getName() << " defend!: +" 
                 << nextIntent.value << " block.\n";
            break;
        case IntentType::BUFF:
            addStrength(nextIntent.value);
            cout << getName() << " meningkatkan strength!: +" 
                 << nextIntent.value << " strength!\n";
            break;
        case IntentType::DEBUFF:
            target.applyWeak(nextIntent.turns);
            cout << getName() << " memberikan soal membingungkan! " 
                 << target.getName() << " kena weak " << nextIntent.turns << " giliran.\n";
            break;
    }       
}

string Enemy::getIntentText() const {
    switch (nextIntent.type) {
    case IntentType::ATTACK:
        return "Serang " + std::to_string(getAttackPower(nextIntent.value));
    case IntentType::DEFEND:
        return "Bertahan, +" + std::to_string(nextIntent.value) + " block";
    case IntentType::BUFF:
        return "Strength, +" + std::to_string(nextIntent.value) + " strength";
    case IntentType::DEBUFF:
        return "Weak, " + std::to_string(nextIntent.turns) + " giliran";
    }
    return "?";
}