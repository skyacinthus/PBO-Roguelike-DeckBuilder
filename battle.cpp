#include "battle.h"
#include "player.h"
#include "enemy.h"
#include <iostream>
#include <stdexcept>
#include <string>
using namespace std;

static string statusTags(const Character& c) {
    string s;
    if (c.getStrength() != 0) s += "  Str " + to_string(c.getStrength());
    if (c.getWeak() > 0)      s += "  Weak " + to_string(c.getWeak());
    return s;
}

Battle::Battle(Player& player, Enemy& enemy) : player(player), enemy(enemy), turnCounter(0) {}

bool Battle::run(){
    player.startBattle();
    enemy.decideNextAction();
    while(player.isAlive() && enemy.isAlive()) {
        turnCounter++;
        playerTurn();
        if (!enemy.isAlive()) break;
        enemyTurn();
    }
    if (player.isAlive()) {
        cout << "Kamu menang!! :D" << endl;
    } else {
        cout << "Kamu kalah :((" << endl;
    }
    return player.isAlive();
}

void Battle::playerTurn(){
    player.startTurn();
    while(player.isAlive() && enemy.isAlive()) {
        printStatus();
        int choice = readInput();
        if (choice == 0) {
            break;
        }
        if (choice < 0 || choice > player.getHandSize()) {
            cout << "Pilihan tidak valid" << endl;
            continue;
        }

        if (player.playCard(choice - 1, enemy)) {
            if (!enemy.isAlive()) {
                return;
            }
        } else {
            cout << "Gagal memainkan kartu. Cek energy atau index kartu." << endl;
        }
    }
    player.endTurn();
}

void Battle::enemyTurn(){
    enemy.startTurn();
    enemy.executeIntent(player);
    if (player.isAlive()) {
        enemy.endTurnEffects();
        enemy.decideNextAction();
    }
}

void Battle::printStatus(){
    cout << "\n=============== Giliran " << turnCounter << " ===============\n";

    // enemy
    cout << enemy.getName()
         << "   HP " << enemy.getHP() << "/" << enemy.getMaxHP()
         << "   Block " << enemy.getBlock()
         << statusTags(enemy) << "\n";
    cout << "   Niat: " << enemy.getIntentText() << "\n";
    cout << "---------------------------------------------\n";

    // player
    cout << player.getName()
         << "   HP " << player.getHP() << "/" << player.getMaxHP()
         << "   Block " << player.getBlock()
         << "   Energi " << player.getEnergy() << "/" << player.getMaxEnergy()
         << statusTags(player) << "\n";

    // hand
    cout << "Kartu:\n";
    if (player.getHandSize() == 0) {
        cout << "[0] Selesaikan Turn \n";
    } else {
        player.printHand();
    }
}

int Battle::readInput() {
    cout << "Pilih kartu (1-" << player.getHandSize() << "), 0 = akhir giliran: ";
    string line;
    if (!getline(cin, line)) {
        return 0;
    }
    try {
        return stoi(line);
    } catch (const invalid_argument&) {
        cout << "Input tidak valid.\n";
        return -1;
    } catch (const out_of_range&) {
        cout << "Input di luar range.\n";
        return -1;
    }
}