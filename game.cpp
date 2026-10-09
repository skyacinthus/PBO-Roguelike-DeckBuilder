#include "game.h"
#include <cstdlib>
#include <iostream>
#include <string>
using namespace std;

const int ROOMS_BEFORE_BOSS = 8;  

static int askNumber(int low, int high) {
    while (true) {
        cout << "Pilihan: ";
        string line;
        if (!getline(cin, line)) return low;         
        try {
            int n = stoi(line);
            if (n >= low && n <= high) return n;
        } catch (...) {
            // tny lagisampai ada input sesuai
        }
        cout << "Masukkan angka " << low << " sampai " << high << ".\n";
    }
}

Game::Game() : roomsCleared(0) {}

vector<unique_ptr<Room>> Game::generateRoomChoices(int roomNumber) {
    vector<unique_ptr<Room>> choices;
    bool hasHeal = false;

    for (int i = 0; i < 3; i++) {
        int roll = rand() % 100;
        if (roomNumber == 1 || roll < 55) {
            choices.push_back(make_unique<BattleRoom>(EnemyTier::COMMON)); 
        } else if (roll < 75) {
            choices.push_back(make_unique<HealRoom>());           
            hasHeal = true;
        } else if (roll < 90 || roomNumber < 4) {
            choices.push_back(make_unique<TreasureRoom>());          
        } else {
            choices.push_back(make_unique<BattleRoom>(EnemyTier::ELITE)); 
        }
    }

    if (!hasHeal && player.getHP() * 2 < player.getMaxHP()) {
        choices[0] = make_unique<HealRoom>();
    }
    return choices;
}

void Game::run() {
    cout << "===== ROGUELIKE KULIAH =====\n";
    cout << "bertahan sampai matkul terakhir hmzzz (sampai sem 3 doang sih)\n";

    for (int room = 1; room <= ROOMS_BEFORE_BOSS; room++) {
        cout << "\n--- Ruangan " << room << " dari " << (ROOMS_BEFORE_BOSS + 1)
             << " (HP " << player.getHP() << "/" << player.getMaxHP() << ") ---\n";

        vector<unique_ptr<Room>> choices = generateRoomChoices(room);
        for (int i = 0; i < (int)choices.size(); i++) {
            cout << "  " << (i + 1) << ") " << choices[i]->getDescription() << "\n";
        }

        int pick = askNumber(1, (int)choices.size());
        choices[pick - 1]->enter(player);            

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
        cout << "SELAMAT! ISIS berhasil kamu kalahkan. Kamu lulus (semester 3)!\n";
    } else {
        cout << "GAME OVER. Kamu gugur setelah melewati " << roomsCleared << " ruangan.\n";
    }
    cout << "=============================\n";
}