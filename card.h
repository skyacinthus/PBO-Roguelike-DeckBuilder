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
    CardId id;

public:
    Card(CardId id, const string& name, int cost, Rarity rarity = Rarity::COMMON)
        : name(name), cost(cost), rarity(rarity) {}
    virtual ~Card() = default;

    virtual void play(Player& user, Character& target) = 0;
    virtual string getDescription() const = 0;

    const string& getName() const { return name; }
    int getCost() const { return cost; }
    Rarity getRarity() const { return rarity; }
    CardId getID() const { return id;}
};

class AttackCard : public Card {
private:
    int damage;
public:
    AttackCard(CardId id, const string& name, int cost, int damage, Rarity r = Rarity::COMMON);
    void play(Player& user, Character& target) override;
    string getDescription() const override;
};

class DefenseCard : public Card {
private:
    int block;
public:
    DefenseCard(CardId id, const string& name, int cost, int block, Rarity r = Rarity::COMMON);
    void play(Player& user, Character& target) override;
    string getDescription() const override;
};

class DebuffCard : public Card {
private:
    int weakTurns;
public:
    DebuffCard(CardId id, const string& name, int cost, int weakTurns, Rarity r = Rarity::COMMON);
    void play(Player& user, Character& target) override;
    string getDescription() const override;
};

class BuffCard : public Card {
private:
    int energyGain;
    int strengthGain;
public:
    BuffCard(CardId id, const string& name, int cost, int energyGain, int strengthGain,
             Rarity r = Rarity::COMMON);
    void play(Player& user, Character& target) override;
    string getDescription() const override;
};

unique_ptr<Card> createCard(CardId id);
vector<unique_ptr<Card>> createStarterDeck();
vector<CardId> getRewardPool(Rarity rarity);   // untuk TreasureRoom

#endif // CARD_H