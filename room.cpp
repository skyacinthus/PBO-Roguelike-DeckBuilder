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

static void offerReward(Player& player, Rarity rarity) {
    vector<CardId> pool = getRewardPool(rarity);
    int count = min(3, (int)pool.size());

    vector<unique_ptr<Card>> offers;
    for (int i = 0; i < count; i++) {
        int j = i + rand() % ((int)pool.size() - i);
        swap(pool[i], pool[j]);
        offers.push_back(createCard(pool[i]));
    }

    cout << "\n=== Pilih satu kartu baru ===\n";
    for (int i = 0; i < count; i++) {
        cout << "  " << (i + 1) << ") " << offers[i]->getName() << " ("
             << offers[i]->getCost() << ") - " << offers[i]->getDescription() << "\n";
    }
    cout << "  0) Lewati\n";

    int choice = -1;
    while (choice < 0 || choice > count) {
        cout << "Pilihan: ";
        string line;
        if (!getline(cin, line)) return;            // end of input: skip
        try { choice = stoi(line); } catch (...) { choice = -1; }
    }
    if (choice == 0) return;

    cout << offers[choice - 1]->getName() << " masuk ke deck-mu.\n";
    player.addCardToDeck(std::move(offers[choice - 1]));
}

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
    
    bool won = battle.run();
    if (won && tier != EnemyTier::BOSS) {
        offerReward(player, tier == EnemyTier::ELITE ? Rarity::RARE : Rarity::COMMON);
    }
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
    offerReward(player, Rarity::RARE);
}

string TreasureRoom::getDescription() const {
    return "Treasure Room";
}