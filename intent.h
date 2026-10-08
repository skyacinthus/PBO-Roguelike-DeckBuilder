#ifndef INTENT_H
#define INTENT_H

#include <string>
using namespace std; 

enum class IntentType {
    ATTACK,
    DEFEND,
    BUFF,
    DEBUFF
};

struct Intent {
    IntentType type;
    int value; 
    int turns;
};

class EnemyIntent {
public:
    Intent intent;

    EnemyIntent(IntentType type, int value, int turns)
        : intent{type, value, turns} {}
};

#endif