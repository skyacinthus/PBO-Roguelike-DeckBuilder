#ifndef ENEMIES_H
#define ENEMIES_H

#include "enemy.h"

class ProgDas : public Enemy {
    private: 
        int turnCounter;
    public: 
        ProgDas();
        void decideNextAction() override;
};

class PVA : public Enemy {
    public:
        PVA();
        void decideNextAction() override;
};

class ALin : public Enemy {
    private:
        int turnCounter;
    public:
        ALin();
        void decideNextAction() override;
};

class MatDis : public Enemy {
    private:
        int turnCounter;
    public:
        MatDis();
        void decideNextAction() override;
};

class Kalkulus : public Enemy {
    private:
        int turnCounter;
    public:
        Kalkulus();
        void decideNextAction() override;
        void endTurnEffects() override;
};

class ISIS  : public Enemy {
    private:
        int turnCounter;
        int phase;
    public:
        ISIS();
        void decideNextAction() override;
};

#endif