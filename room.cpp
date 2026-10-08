#include "room.h"
#include "player.h"      
#include <iostream>
using namespace std;

BattleRoom::BattleRoom(EnemyTier tier) : tier(tier) {}

void BattleRoom::enter(Player& player) {
    cout << "Memasuki pertarungan!\n";
    // TODO: pilih musuh acak sesuai tier, lalu jalankan Battle
    // contoh nanti: Battle battle(player, enemy); battle.run();
}

string BattleRoom::getDescription() const {
    switch (tier) {
        case EnemyTier::COMMON: return "Common Enemy";
        case EnemyTier::ELITE:  return "Elite Enemy";
        case EnemyTier::BOSS:   return "Boss";
    }
    return "Unknown";
}

void HealRoom::enter(Player& player) {
    int amount = player.getMaxHP() * 3 / 10;
    player.heal(amount);
    cout << "Kamu beristirahat dan memulihkan " << amount << " HP.\n";
}

string HealRoom::getDescription() const {
    return "Heal Room";
}

void TreasureRoom::enter(Player& player) {
    cout << "Kamu menemukan harta karun!\n";
    // TODO: beri kartu baru, misalnya:
    // player.addCardToDeck(make_unique<AttackCard>(...));
}

string TreasureRoom::getDescription() const {
    return "Treasure Room";
}