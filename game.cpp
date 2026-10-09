#include "game.h"
#include <cstdlib>
#include <iostream>
#include <string>
using namespace std;

const int ROOMS_BEFORE_BOSS = 9;   
const int MAX_TREASURE_ROOMS = 2;  

static int askNumber(int lo, int hi) {
    while (true) {
        cout << "Pilihan: ";
        string line;
        if (!getline(cin, line) || line == "q" || line == "Q") quitGame();         
        try {
            int n = stoi(line);
            if (n >= lo && n <= hi) return n;
        } catch (...) {
            
        }
        cout << "Masukkan angka " << lo << " sampai " << hi << ".\n";
    }
}

Game::Game() : roomsCleared(0), treasureCount(0) {}

vector<unique_ptr<Room>> Game::generateRoomChoices(int roomNumber) {
    vector<unique_ptr<Room>> choices;
    bool hasHeal = false;

    for (int i = 0; i < 3; i++) {
        int roll = rand() % 100;
        if (roomNumber == 1 || roll < 55) {
            choices.push_back(make_unique<BattleRoom>(EnemyTier::COMMON));   
        } else if (roll < 70) {
            choices.push_back(make_unique<HealRoom>());                      
            hasHeal = true;
        } else if (roll < 80 && treasureCount < MAX_TREASURE_ROOMS) {
            choices.push_back(make_unique<TreasureRoom>());                  
        } else if (roll >= 90 && roomNumber >= 4) {
            choices.push_back(make_unique<BattleRoom>(EnemyTier::ELITE));    
        } else {
            choices.push_back(make_unique<BattleRoom>(EnemyTier::COMMON)); 
        }
    }

    if (!hasHeal && player.getHP() * 2 < player.getMaxHP()) {
        choices[0] = make_unique<HealRoom>();
    }
    return choices;
}

void Game::run() {
    cout << "===== ROGUELIKE KULIAH =====\n";
    cout << "Bertahan sampai matkul terakhir: ISIS!\n";

    for (int room = 1; room <= ROOMS_BEFORE_BOSS; room++) {
        cout << "\n--- Ruangan " << room << " dari " << (ROOMS_BEFORE_BOSS + 1)
             << " (HP " << player.getHP() << "/" << player.getMaxHP() << ") ---\n";

        vector<unique_ptr<Room>> choices = generateRoomChoices(room);
        for (int i = 0; i < (int)choices.size(); i++) {
            cout << "  " << (i + 1) << ") " << choices[i]->getDescription() << "\n";
        }

        int pick = askNumber(1, (int)choices.size());
        if (dynamic_cast<TreasureRoom*>(choices[pick - 1].get())) {
            treasureCount++;                         // count treasure rooms the player actually takes
        }
        choices[pick - 1]->enter(player);            // polymorphism: each room does its own thing

        if (!player.isAlive()) {
            showEndScreen(false);
            return;
        }
        roomsCleared++;
    }

    cout << "\n--- Ruangan terakhir: BOSS ---\n";
    BattleRoom boss(EnemyTier::BOSS);
    boss.enter(player);
    showEndScreen(player.isAlive());
}

void Game::showEndScreen(bool won) {
    cout << "\n=============================\n";
    if (won) {
        cout << "SELAMAT! ISIS berhasil kamu kalahkan. Kamu lulus!\n";
    } else {
        cout << "GAME OVER. Kamu gugur setelah melewati " << roomsCleared << " ruangan.\n";
    }
    cout << "=============================\n";
}