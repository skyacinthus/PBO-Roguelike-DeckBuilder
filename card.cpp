#include "card.h"
#include "player.h"
#include <iostream>
using namespace std;

AttackCard::AttackCard(CardId id, const string& name, int cost, int damage, Rarity r)
    : Card(id, name, cost, r), damage(damage) {}

void AttackCard::play(Player& user, Character& target) {
    int dmg = user.getAttackPower(damage);
    int lost = target.takeDamage(dmg);
    cout << user.getName() << " memakai " << getName() << ": "
         << target.getName() << " kehilangan " << lost << " HP.\n";
}

string AttackCard::getDescription() const {
    return "Beri " + to_string(damage) + " damage";
}

DefenseCard::DefenseCard(CardId id, const string& name, int cost, int block, Rarity r)
    : Card(id, name, cost, r), block(block) {}

void DefenseCard::play(Player& user, Character&) {
    user.addBlock(block);
    cout << user.getName() << " memakai " << getName() << ": +" << block << " block.\n";
}

string DefenseCard::getDescription() const {
    return "Dapat " + to_string(block) + " block";
}

DebuffCard::DebuffCard(CardId id, const string& name, int cost, int weakTurns, Rarity r)
    : Card(id, name, cost, r), weakTurns(weakTurns) {}

void DebuffCard::play(Player& user, Character& target) {
    target.applyWeak(weakTurns);
    cout << user.getName() << " memakai " << getName() << ": "
         << target.getName() << " weak " << weakTurns << " giliran.\n";
}

string DebuffCard::getDescription() const {
    return "Musuh weak " + to_string(weakTurns) + " giliran";
}

BuffCard::BuffCard(CardId id, const string& name, int cost, int energyGain, int strengthGain, Rarity r)
    : Card(id, name, cost, r), energyGain(energyGain), strengthGain(strengthGain) {}

void BuffCard::play(Player& user, Character&) {
    if (energyGain > 0)   user.addEnergy(energyGain);
    if (strengthGain > 0) user.addStrength(strengthGain);
    cout << user.getName() << " memakai " << getName() << ".\n";
}

string BuffCard::getDescription() const {
    string s;
    if (energyGain > 0)   s += "+" + to_string(energyGain) + " energi ";
    if (strengthGain > 0) s += "+" + to_string(strengthGain) + " strength";
    return s;
}

unique_ptr<Card> createCard(CardId id) {
    switch (id) {
        //attack
        case CardId::LATIHAN_SOAL:     
            return make_unique<AttackCard>(id, "Latihan Soal", 1, 5);
        case CardId::NGERJAIN_PR:      
            return make_unique<AttackCard>(id, "Ngerjain PR", 2, 12);
        case CardId::BELAJAR_BEGADANG: 
            return make_unique<AttackCard>(id, "Belajar Begadang", 3, 18);
        case CardId::TUTOR_YOUTUBE:    
            return make_unique<AttackCard>(id, "Nonton Tutor Prof India di YT", 2, 15, Rarity::RARE);

        // def
        case CardId::CATATAN_RAPI:     
            return make_unique<DefenseCard>(id, "Catatan Rapi", 1, 5);
        case CardId::CHEATSHEET:       
            return make_unique<DefenseCard>(id, "Buat Cheatsheet", 2, 10);
        case CardId::MASTERAN:         
            return make_unique<DefenseCard>(id, "Dapat Masteran", 2, 15, Rarity::RARE);

        // debuff
        case CardId::PERPANJANGAN_DL:  
            return make_unique<DebuffCard>(id, "Minta Perpanjangan DL", 1, 2);
        case CardId::KELAS_DITIADAKAN: 
            return make_unique<DebuffCard>(id, "Kelas Ditiadakan", 2, 3);

        // buff
        case CardId::KOPI:             
            return make_unique<BuffCard>(id, "Kopi", 0, 1, 0);
        case CardId::BELAJAR_KELOMPOK: 
            return make_unique<BuffCard>(id, "Belajar Kelompok", 1, 0, 1);
        case CardId::TANYA_TEMAN:      
            return make_unique<BuffCard>(id, "Tanya Teman", 2, 0, 2);
    }
    return nullptr;
}

vector<unique_ptr<Card>> createStarterDeck() {
    const pair<CardId, int> starter[] = {
        { CardId::LATIHAN_SOAL, 3 },
        { CardId::NGERJAIN_PR, 1 },
        { CardId::CATATAN_RAPI, 2 },
        { CardId::PERPANJANGAN_DL, 1 },
        { CardId::KOPI, 1 },
    };

    vector<unique_ptr<Card>> deck;
    for (const auto& entry : starter)
        for (int i = 0; i < entry.second; i++)
            deck.push_back(createCard(entry.first));   // objek baru tiap kali
    return deck;
}

vector<CardId> getRewardPool(Rarity rarity) {
    if (rarity == Rarity::RARE)
        return { CardId::TUTOR_YOUTUBE, CardId::MASTERAN };
    return { CardId::BELAJAR_BEGADANG, CardId::CHEATSHEET, CardId::KELAS_DITIADAKAN,
             CardId::BELAJAR_KELOMPOK, CardId::TANYA_TEMAN };
}