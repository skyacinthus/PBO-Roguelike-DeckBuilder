// Throwaway checker for ProgDas, Statistika, AljabarLinear, MatDis, Kalkulus.
// (ISIS is not covered.) Not part of the game: do NOT add it to the real build.
//
// Needs: character.h/.cpp, intent.h, enemy.h/.cpp, enemies.h/.cpp
// Assumes: Weak is a duration (25% less damage, ticks down in endTurnEffects()),
//          and for a DEBUFF intent, `value` = number of Weak turns.
//
// Build:  g++ -std=c++17 -Wall -Wextra test_enemies.cpp enemies.cpp enemy.cpp character.cpp -o test_enemies
// Run:    ./test_enemies
//
// If you retune a number in enemies.cpp, change the matching constant in the
// EXPECTED VALUES block below.

#include "character.h"
#include "enemy.h"
#include "enemies.h"
#include "intent.h"
#include <cstdlib> // for rand()

#include <iostream>
#include <vector>
#include <memory>
#include <string>

using namespace std;

// ===================== EXPECTED VALUES (edit if you retune) =====================
struct Move { IntentType type; int value; };

const int PROGDAS_HP = 32;
const vector<Move> PROGDAS_PATTERN = {
    {IntentType::ATTACK, 7}, {IntentType::ATTACK, 7}, {IntentType::DEFEND, 6}};

const int STATISTIKA_HP = 36;
const int STATISTIKA_ATTACK = 8, STATISTIKA_DEFEND = 5;   // 60% attack / 40% defend

const int ALJABAR_HP = 40;
const int ALJABAR_WEAK_TURNS = 2;
const vector<Move> ALJABAR_PATTERN = {
    {IntentType::DEBUFF, ALJABAR_WEAK_TURNS}, {IntentType::ATTACK, 8}, {IntentType::ATTACK, 6}};

const int MATDIS_HP = 50;
const int MATDIS_BLOCK = 10, MATDIS_ATTACK = 12;
const vector<Move> MATDIS_PATTERN = {
    {IntentType::DEFEND, MATDIS_BLOCK}, {IntentType::ATTACK, MATDIS_ATTACK}};

const int KALKULUS_HP = 60;
const vector<Move> KALKULUS_PATTERN = {
    {IntentType::ATTACK, 6}, {IntentType::ATTACK, 6}, {IntentType::DEFEND, 8}};
// =================================================================================

int failures = 0;
#define CHECK(cond, msg) \
    do { if (cond) cout << "  PASS: " << msg << "\n"; \
         else { cout << "  FAIL: " << msg << "\n"; failures++; } } while (0)

// Stand-in for the player.
class Dummy : public Character {
public:
    Dummy() : Character("Dummy", 1000) {}
    void startTurn() override { clearBlock(); }
};

string typeName(IntentType t) {
    switch (t) {
        case IntentType::ATTACK: return "ATTACK";
        case IntentType::DEFEND: return "DEFEND";
        case IntentType::BUFF:   return "BUFF";
        case IntentType::DEBUFF: return "DEBUFF";
    }
    return "?";
}

string describe(const Move& m) { return typeName(m.type) + " " + to_string(m.value); }

// One full enemy turn, in the order Battle should use:
// startTurn -> executeIntent -> endTurnEffects -> decideNextAction.
// The intent shown to the player is the one that was chosen BEFORE this call.
void enemyTurn(Enemy& e, Character& target) {
    e.startTurn();
    e.executeIntent(target);
    e.endTurnEffects();
    e.decideNextAction();
}

// Plays `turns` enemy turns and compares each shown intent to the expected cycle.
void checkPattern(Enemy& e, const vector<Move>& pattern, int turns, const string& label) {
    Dummy d;
    e.decideNextAction();                       // battle start: first intent
    bool allMatch = true;
    string seen;
    for (int t = 0; t < turns; t++) {
        Move expected = pattern[t % pattern.size()];
        const Intent& got = e.getNextIntent();
        seen += (t ? ", " : "") + typeName(got.type) + " " + to_string(got.value);
        if (got.type != expected.type || got.value != expected.value) {
            allMatch = false;
            cout << "    turn " << (t + 1) << ": expected " << describe(expected)
                 << " but got " << typeName(got.type) << " " << got.value << "\n";
        }
        enemyTurn(e, d);
    }
    cout << "    seen: " << seen << "\n";
    CHECK(allMatch, label + " pattern repeats correctly over " + to_string(turns) + " turns");
}

void checkBasics(Enemy& e, int hp, EnemyTier tier, const string& label) {
    CHECK(e.getMaxHP() == hp && e.getHP() == hp,
          label + " starts at full HP " + to_string(hp) + " (got " + to_string(e.getHP()) + "/" + to_string(e.getMaxHP()) + ")");
    CHECK(e.getTier() == tier, label + " has the right tier");
    CHECK(e.isAlive() && e.getBlock() == 0 && e.getStrength() == 0 && e.getWeak() == 0,
          label + " starts alive with no block, Strength or Weak");
}

int main() {
    // ---------------------------------------------------------------- ProgDas
    cout << "== ProgDas (common): Attack 7, Attack 7, Defend 6 ==\n";
    {
        ProgDas e;
        checkBasics(e, PROGDAS_HP, EnemyTier::COMMON, "ProgDas");
        checkPattern(e, PROGDAS_PATTERN, 9, "ProgDas");

        // damage actually dealt: 2 attacks of 7 in one cycle
        ProgDas e2;
        Dummy d;
        e2.decideNextAction();
        for (int i = 0; i < 3; i++) enemyTurn(e2, d);
        CHECK(d.getHP() == 1000 - 14, "one full cycle deals 14 damage (got " + to_string(1000 - d.getHP()) + ")");
        CHECK(e2.getBlock() == 6, "Defend turn leaves the enemy with 6 block");

        // two instances must not share a counter
        ProgDas a, b;
        a.decideNextAction(); a.decideNextAction(); a.decideNextAction();
        b.decideNextAction();
        CHECK(b.getNextIntent().type == IntentType::ATTACK && b.getNextIntent().value == 7,
              "a second ProgDas starts at the beginning of the pattern (counter not shared)");
    }

    // ------------------------------------------------------------- Statistika
    cout << "== Statistika (common): random Attack 8 (60%) / Defend 5 (40%) ==\n";
    {
        PVA e;
        checkBasics(e, STATISTIKA_HP, EnemyTier::COMMON, "Statistika");
        srand(42);
        const int N = 2000;
        int attacks = 0, defends = 0, invalid = 0;
        for (int i = 0; i < N; i++) {
            e.decideNextAction();
            const Intent& in = e.getNextIntent();
            if (in.type == IntentType::ATTACK && in.value == STATISTIKA_ATTACK) attacks++;
            else if (in.type == IntentType::DEFEND && in.value == STATISTIKA_DEFEND) defends++;
            else invalid++;
        }
        cout << "    " << N << " picks: " << attacks << " attack, " << defends << " defend, " << invalid << " other\n";
        CHECK(invalid == 0, "only ever picks Attack " + to_string(STATISTIKA_ATTACK) + " or Defend " + to_string(STATISTIKA_DEFEND));
        CHECK(attacks >= 1100 && attacks <= 1300, "attack share is about 60% (55% to 65% accepted)");
        CHECK(attacks > 0 && defends > 0, "both moves actually occur");
    }

    // ----------------------------------------------------------- AljabarLinear
    cout << "== AljabarLinear (common): Weak 2 turns, Attack 7, Attack 7 ==\n";
    {
        ALin e;
        checkBasics(e, ALJABAR_HP, EnemyTier::COMMON, "AljabarLinear");
        checkPattern(e, ALJABAR_PATTERN, 9, "AljabarLinear");

        ALin e2;
        Dummy d;
        e2.decideNextAction();                  // first intent is the debuff
        e2.executeIntent(d);
        CHECK(d.getWeak() == ALJABAR_WEAK_TURNS, "debuff gives the PLAYER Weak " + to_string(ALJABAR_WEAK_TURNS) + " (got " + to_string(d.getWeak()) + ")");
        CHECK(e2.getWeak() == 0, "debuff does not weaken the enemy itself");
        CHECK(d.getHP() == 1000, "debuff deals no damage");
        d.endTurnEffects(); d.endTurnEffects();
        CHECK(d.getWeak() == 0, "player's Weak wears off after " + to_string(ALJABAR_WEAK_TURNS) + " of their turns");
    }

    // ------------------------------------------------------------------ MatDis
    cout << "== MatDis (elite): Defend 10, Attack 12 ==\n";
    {
        MatDis e;
        checkBasics(e, MATDIS_HP, EnemyTier::ELITE, "MatDis");
        checkPattern(e, MATDIS_PATTERN, 8, "MatDis");

        MatDis e2;
        Dummy d;
        e2.decideNextAction();                  // Defend
        e2.startTurn();
        e2.executeIntent(d);
        CHECK(e2.getBlock() == MATDIS_BLOCK, "Defend gives the enemy " + to_string(MATDIS_BLOCK) + " block");
        int hpLost = e2.takeDamage(14);
        CHECK(hpLost == 14 - MATDIS_BLOCK && e2.getBlock() == 0, "a 14-damage hit into the block takes only " + to_string(14 - MATDIS_BLOCK) + " HP");
        e2.decideNextAction();                  // Attack
        e2.startTurn();
        e2.executeIntent(d);
        CHECK(d.getHP() == 1000 - MATDIS_ATTACK, "Attack deals " + to_string(MATDIS_ATTACK) + " damage");

        MatDis e3;
        Dummy d3;
        e3.decideNextAction();
        e3.executeIntent(d3);                   // block 10
        e3.startTurn();                         // its next turn begins
        CHECK(e3.getBlock() == 0, "startTurn() clears the enemy's old block");
    }

    // ---------------------------------------------------------------- Kalkulus
    cout << "== Kalkulus (elite): Attack 6, Attack 6, Defend 8, +1 Strength each of its turns ==\n";
    {
        Kalkulus e;
        checkBasics(e, KALKULUS_HP, EnemyTier::ELITE, "Kalkulus");
        {
            Kalkulus p;
            checkPattern(p, KALKULUS_PATTERN, 6, "Kalkulus");
        }

        // Strength ramp: 0 on turn 1, 1 on turn 2, 2 on turn 3, ...
        Kalkulus k;
        Dummy d;
        Character* asCharacter = &k;            // endTurnEffects() must dispatch to the override
        k.decideNextAction();
        bool rampOk = true;
        bool damageOk = true;
        for (int turn = 1; turn <= 5; turn++) {
            Move base = KALKULUS_PATTERN[(turn - 1) % KALKULUS_PATTERN.size()];
            int strengthNow = k.getStrength();
            if (strengthNow != turn - 1) {
                rampOk = false;
                cout << "    turn " << turn << ": expected Strength " << (turn - 1) << " before acting, got " << strengthNow << "\n";
            }
            int before = d.getHP();
            k.startTurn();
            k.executeIntent(d);
            int dealt = before - d.getHP();
            int expectedDmg = (base.type == IntentType::ATTACK) ? base.value + (turn - 1) : 0;
            if (dealt != expectedDmg) {
                damageOk = false;
                cout << "    turn " << turn << ": expected damage " << expectedDmg << ", got " << dealt << "\n";
            }
            asCharacter->endTurnEffects();      // as Battle would, via a base reference
            k.decideNextAction();
        }
        CHECK(rampOk, "Strength is 0, 1, 2, 3, 4 on turns 1 to 5");
        CHECK(damageOk, "damage rises with Strength (6, 7, no attack, 9, 10)");
        CHECK(k.getStrength() == 5, "Strength is 5 after 5 turns (got " + to_string(k.getStrength()) + ")");

        // the override must still tick Weak down (it should call Character::endTurnEffects)
        Kalkulus w;
        w.applyWeak(2);
        Character* cw = &w;
        cw->endTurnEffects();
        CHECK(w.getWeak() == 1, "Kalkulus's override still ticks Weak down (2 -> " + to_string(w.getWeak()) + ")");
    }

    // ------------------------------------------------- all through Enemy*
    cout << "== Polymorphism: all five through Enemy* ==\n";
    {
        vector<unique_ptr<Enemy>> roster;
        roster.push_back(make_unique<ProgDas>());
        roster.push_back(make_unique<PVA>());
        roster.push_back(make_unique<ALin>());
        roster.push_back(make_unique<MatDis>());
        roster.push_back(make_unique<Kalkulus>());
        Dummy d;
        bool allSet = true;
        for (auto& e : roster) {
            e->decideNextAction();
            if (e->getNextIntent().value <= 0) allSet = false;
            for (int i = 0; i < 20; i++) enemyTurn(*e, d);   // must not crash
            cout << "    " << e->getName() << ": ok\n";
        }
        CHECK(allSet, "every enemy sets a real intent through a base pointer");
    }

    cout << "\n" << (failures == 0 ? "ALL CHECKS PASSED" : to_string(failures) + " CHECK(S) FAILED") << "\n";
    return failures == 0 ? 0 : 1;
}