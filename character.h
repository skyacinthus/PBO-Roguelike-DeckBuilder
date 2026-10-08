#ifndef CHARA_H
#define CHARA_H
#include <string>
using namespace std;

class Character {
private:
    string name;
    int hp;
    int maxHp;
    int block;
    int strength;   
    int weak;       
protected:
    void clearBlock();

public:
    Character(const string& name, int maxHp);
    virtual ~Character() = default;  // perlu ga

    virtual void startTurn() = 0;

    int takeDamage(int amount);
    void loseHP(int amount);          
    void heal(int amount);            
    void addBlock(int amount);
    void addStrength(int amount);
    void applyWeak(int turns);

    int getAttackPower(int baseDamage) const;

    void endTurnEffects();

    void resetBattleState();

    bool isAlive() const;

    const string& getName() const { return name; }
    int getHP() const { return hp; }
    int getMaxHP() const { return maxHp; }
    int getBlock() const { return block; }
    int getStrength() const { return strength; }
    int getWeak() const { return weak; }
};
#endif CHARA_H