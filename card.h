#ifndef CARD_H
#define CARD_H

#include <string>
#include <memory>
#include <vector>
using namespace std;

class Player;
class Character;

enum class Rarity { COMMON, RARE };
enum class CardId {
    LATIHAN_SOAL, NGERJAIN_PR, BELAJAR_BEGADANG, TUTOR_YOUTUBE,
    CATATAN_RAPI, CHEATSHEET, MASTERAN,
    PERPANJANGAN_DL, KELAS_DITIADAKAN,
    KOPI, BELAJAR_KELOMPOK, TANYA_TEMAN
};

class Card {
private:
    string name;
    int cost;
    Rarity rarity;
public:
    Card(const string& name, int cost, Rarity rarity = Rarity::COMMON)
        : name(name), cost(cost), rarity(rarity) {}
    virtual ~Card() = default;

    virtual void play(Player& user, Character& target) = 0;
    virtual string getDescription() const = 0;

    const string& getName() const { return name; }
    int getCost() const { return cost; }
    Rarity getRarity() const { return rarity; }
};

class AttackCard : public Card {
private:
    int damage;
public:
    AttackCard(const string& name, int cost, int damage, Rarity r = Rarity::COMMON);
    void play(Player& user, Character& target) override;
    string getDescription() const override;
};

class DefenseCard : public Card {
private:
    int block;
public:
    DefenseCard(const string& name, int cost, int block, Rarity r = Rarity::COMMON);
    void play(Player& user, Character& target) override;
    string getDescription() const override;
};

class DebuffCard : public Card {
private:
    int weakTurns;
public:
    DebuffCard(const string& name, int cost, int weakTurns, Rarity r = Rarity::COMMON);
    void play(Player& user, Character& target) override;
    string getDescription() const override;
};

class BuffCard : public Card {
private:
    int energyGain;
    int strengthGain;
public:
    BuffCard(const string& name, int cost, int energyGain, int strengthGain,
             Rarity r = Rarity::COMMON);
    void play(Player& user, Character& target) override;
    string getDescription() const override;
};

unique_ptr<Card> createCard(CardId id);
vector<unique_ptr<Card>> createStarterDeck();
vector<CardId> getRewardPool(Rarity rarity);   // untuk TreasureRoom

#endif // CARD_H