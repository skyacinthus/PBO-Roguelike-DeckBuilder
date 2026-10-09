#include "battle.h"
#include "player.h"
#include "enemy.h"
#include <iostream>
#include <string> 
using namespace std;

Battle::Battle(Player& player, Enemy& enemy) : player(player), enemy(enemy), turnCounter(0) {}

static string statusTags(const Character& c) {
    string s;
    if (c.getStrength() != 0) s += "  Str " + to_string(c.getStrength());
    if (c.getWeak() > 0)      s += "  Weak " + to_string(c.getWeak());
    return s;
} // helper utk nampilin nnt

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
        cout << "You won the battle!" << endl;
    } else {
        cout << "You lost the battle." << endl;
    }
    
    return player.isAlive();
};

void Battle::playerTurn(){
    player.startTurn();
    while(player.isAlive() && enemy.isAlive()) {
        printStatus();
        int choice = readInput();
        if (choice == 0) {
            break; 
        } if (choice < 0 || choice > player.getHandSize()) {
            cout << "Invalid choice. Please try again." << endl;
            continue;
        };

        if (player.playCard(choice - 1, enemy)) {
            if (!enemy.isAlive()) {
                return;                     
            }
        } else {
            cout << "Failed to play card. Check energy or card index." << endl;
        }
    };
    player.endTurn();
};

void Battle::enemyTurn(){
    enemy.startTurn();
    enemy.executeIntent(player);
    if (player.isAlive()) {
        enemy.endTurnEffects();
        enemy.decideNextAction();
    }
};

void Battle::printStatus(){
    cout << "\n=============== TURN " << turnCounter << " ===============\n";
 
    // enemy
    cout << enemy.getName()
         << "   HP " << enemy.getHP() << "/" << enemy.getMaxHP()
         << "   Block " << enemy.getBlock()
         << statusTags(enemy) << "\n";
    cout << "   Niat: " << enemy.getIntentText() << "\n";
    cout << "---------------------------------------------\n";
 
    cout << player.getName()
         << "   HP " << player.getHP() << "/" << player.getMaxHP()
         << "   Block " << player.getBlock()
         << "   Energi " << player.getEnergy() << "/" << player.getMaxEnergy()
         << statusTags(player) << "\n";
 
    cout << "Kartu:\n";
    if (player.getHandSize() == 0) {
        cout << "  (tidak ada kartu)\n";
    } else {
        player.printHand();
    }
}


int Battle::readInput() {
    // cout buat milih kartu disini atau di playerTurn yah
    string line;
    if (!getline(cin, line)) {
        return 0; 
    }
    try {
        return stoi(line);
    } catch (const invalid_argument&) {
        cout << "Invalid input. Please enter a valid number.\n";
        return -1;
    } catch (const out_of_range&) {
        cout << "Input out of range.\n";
        return -1;
    }
}
