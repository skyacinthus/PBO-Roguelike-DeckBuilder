#ifndef ENEMY_H
#define ENEMY_H

#include <string>
#include "character.h"
#include "intent.h"
using namespace std;

enum class EnemyTier {
    COMMON, 
    ELITE, 
    BOSS
};

class Enemy : public Character {
    private: 
        EnemyTier tier;
    protected:
        Intent nextIntent;
    public:
        Enemy(const string& name, int maxHp, EnemyTier tier);
        virtual ~Enemy() = default;

        void startTurn() override;

        virtual void decideNextAction() = 0;

        void executeIntent(Character& target);

        const Intent& getNextIntent() const { return nextIntent; }
        EnemyTier getTier() const { return tier; }

};

#endif