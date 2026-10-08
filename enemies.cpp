#include "enemies.h"
#include <cstdlib> // untuk fungsi rand di stat

const int PROGDAS_HP = 32;
const int PVA_HP = 36;
const int ALIN_HP = 40;
const int MATDIS_HP = 50;
const int ISIS_HP = 90;

ProgDas::ProgDas() : Enemy("ProgDas", PROGDAS_HP, EnemyTier::COMMON), turnCounter(0) {}

void ProgDas::decideNextAction() {
    switch (turnCounter % 3) {
        case 0: nextIntent = {IntentType::ATTACK, 7, 0}; break;
        case 1: nextIntent = {IntentType::ATTACK, 7, 0}; break;
        case 2: nextIntent = {IntentType::DEFEND, 6, 0}; break;
    }
    turnCounter++;
}

PVA::PVA() : Enemy("PVA", PVA_HP, EnemyTier::COMMON) {}

void PVA::decideNextAction() {
    int action = rand() % 100;
    if (action < 60) {
        nextIntent = {IntentType::ATTACK, 8, 0};
    } else {
        nextIntent = {IntentType::DEFEND, 4, 0};
    }
}

ALin::ALin() : Enemy("ALin", ALIN_HP, EnemyTier::COMMON), turnCounter(0) {}

void ALin::decideNextAction() {
    switch (turnCounter % 3) {
        case 0: nextIntent = {IntentType::DEBUFF, 0, 2}; break;
        case 1: nextIntent = {IntentType::ATTACK, 8, 0}; break;
        case 2: nextIntent = {IntentType::ATTACK, 6, 0}; break;
    }
    turnCounter++;
}

MatDis::MatDis() : Enemy("MatDis", MATDIS_HP, EnemyTier::ELITE), turnCounter(0) {}

void MatDis::decideNextAction() {
    switch (turnCounter % 2) {
        case 0: nextIntent = {IntentType::DEFEND, 10, 0}; break;
        case 1: nextIntent = {IntentType::ATTACK, 12, 0}; break;
    }
    turnCounter++;
}

Kalkulus::Kalkulus() : Enemy("Kalkulus", 60, EnemyTier::ELITE), turnCounter(0) {}

void Kalkulus::decideNextAction() {
    switch (turnCounter % 3) {
        case 0: nextIntent = {IntentType::ATTACK, 6, 0}; break;
        case 1: nextIntent = {IntentType::ATTACK, 6, 0}; break;
        case 2: nextIntent = {IntentType::DEFEND, 8, 0}; break;
    }
    turnCounter++;
}

void Kalkulus::endTurnEffects() {
    Character::endTurnEffects(); 
    if (turnCounter % 3 == 2) {
        addStrength(2);
    }
}

ISIS::ISIS() : Enemy("ISIS", ISIS_HP, EnemyTier::BOSS), turnCounter(0), phase(1) {}

void ISIS::decideNextAction() {
    int hpPercentage = (getHP() * 100) / getMaxHP();
    int newPhase = (hpPercentage > 60) ? 1 : (hpPercentage > 30) ? 2 : 3;
    if (newPhase != phase) {
        phase = newPhase;
        turnCounter = 0;
    }

    switch (phase) {
        case 1:
            switch (turnCounter % 2) {
                case 0: nextIntent = {IntentType::ATTACK, 9, 0}; break;
                case 1: nextIntent = {IntentType::DEFEND, 8, 0}; break;
            }
            break;
        case 2:
            switch (turnCounter % 2) {
                case 0: nextIntent = {IntentType::DEBUFF, 0, 2}; break;
                case 1: nextIntent = {IntentType::ATTACK, 10, 0}; break;
            }
            break;
        case 3:
            switch (turnCounter % 2) {
                case 0: nextIntent = {IntentType::DEFEND, 6, 0}; break;
                case 1: nextIntent = {IntentType::ATTACK, 15, 0}; break;
            }
            break;
    }
    turnCounter++;
}

