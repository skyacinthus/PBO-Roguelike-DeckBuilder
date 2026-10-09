#include "room.h"
#include "player.h" 
#include "battle.h"
#include "enemies.h"     
#include <iostream>
#include <memory>
#include <vector>
#include <cstdlib>

using namespace std;

BattleRoom::BattleRoom(EnemyTier tier) : tier(tier) {}

void BattleRoom::enter(Player& player) {
    cout << "Memasuki pertarungan!\n";
    vector<unique_ptr<Enemy>> possibleEnemies;

    if (tier == EnemyTier::COMMON) {
        possibleEnemies.push_back(make_unique<ProgDas>());
        possibleEnemies.push_back(make_unique<PVA>());
        possibleEnemies.push_back(make_unique<ALin>());
    } else if (tier == EnemyTier::ELITE) {
        possibleEnemies.push_back(make_unique<MatDis>());
        possibleEnemies.push_back(make_unique<Kalkulus>());
    } else if (tier == EnemyTier::BOSS) {
        possibleEnemies.push_back(make_unique<ISIS>());
    }

    int index = rand() % possibleEnemies.size(); // utk random select

    Battle battle(player, *possibleEnemies[index]); // wow cerdas
    battle.run();
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
    vector<CardId> pool = getRewardPool(Rarity::COMMON);
    CardId chosen = pool[rand() % pool.size()];
    unique_ptr<Card> card = createCard(chosen);
    cout << "Kamu mendapat kartu: " << card->getName() << " (" << card->getDescription() << ")\n";
    player.addCardToDeck(std::move(card));
}

string TreasureRoom::getDescription() const {
    return "Treasure Room";
}