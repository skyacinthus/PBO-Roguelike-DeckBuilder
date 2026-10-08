#ifndef BATTLE_H
#define BATTLE_H

class Player;
class Enemy;

class Battle {
    private:
        Player& player;
        Enemy& enemy;
        int turnCounter;

        void playerTurn();
        void enemyTurn();
        void printStatus() const;
        int readInput() const; // utk no kartu, 0 = end turn
    public:
        Battle(Player& player, Enemy& enemy);
        bool run(); // klo menang true klo kalah false
};

#endif