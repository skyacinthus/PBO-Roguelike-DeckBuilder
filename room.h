#ifndef ROOM_H
#define ROOM_H

#include "player.h"
#include "enemy.h"

#include <string>
using namespace std;

class Player;

class Room {
public:
    virtual ~Room() = default;
    virtual void enter(Player& player) = 0;           // polimorfisme di sini
    virtual string getDescription() const = 0;        // untuk ditampilkan saat memilih
};

class BattleRoom : public Room {
private:
    EnemyTier tier;
public:
    BattleRoom(EnemyTier tier);
    void enter(Player& player) override;
    string getDescription() const override;
};

class HealRoom : public Room {
public:
    void enter(Player& player) override;
    string getDescription() const override;
};

class TreasureRoom : public Room {
public:
    void enter(Player& player) override;    
    string getDescription() const override;
};
#endif