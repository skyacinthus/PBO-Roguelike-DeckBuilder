#ifndef ROOM_H
#define ROOM_H

#include <string>
using namespace std;

class Player;

class Room {
public:
    virtual ~Room() = default;
    virtual void enter(Player& player) = 0;           // polimorfisme di sini
    virtual string getDescription() const = 0;        // untuk ditampilkan saat memilih
};
enum class EnemyTier { COMMON, ELITE, BOSS }; 

class BattleRoom : public Room {
private:
    EnemyTier tier;
public:
    BattleRoom(EnemyTier tier) : tier(tier) {}
    void enter(Player& player) override;
    string getDescription() const override;
};

class HealRoom : public Room {
public:
    void enter(Player& player) override { player.heal(player.getMaxHP() * 3 / 10); }
    string getDescription() const override { return "Heal Room"; }
};

class TreasureRoom : public Room {
public:
    void enter(Player& player) override;    
    string getDescription() const override { return "Treasure Room"; }
};
#endif