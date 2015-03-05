#include <iostream>
#include <string>
#include <sstream>
#include <cstdlib>
#include "map.h"
#include "cell.h"
#include "character.h"
#include "treasure.h"
#include "player.h"
#include "human.h"
using namespace std;


Player::Player(int row, int col, Map *mp, int maxHealth, int health, int atk, int def):
    Character(row, col, mp, '@', "PC", maxHealth, health, atk, def),
    gold(0),
    score(0) {}

Player::~Player() {}

int Player::takeTreasure(Cell *cll) {
    int amt = cll->getOccupant()->getVal();
    gold += amt;
    addScore(amt);

    cll->clearOccupant(true);

    return amt;
}

void Player::addScore(int points) {
    score += points;
}

int Player::getScore() {
    return score;
}

int Player::subGold(int amt) {
    if (gold<amt) {
        amt = gold;
        gold=0;
    } else {
        gold -= amt;
    }
    return amt;
}

bool Player::action(string dir) {
    stringstream ss;
    bool success=true;
    bool moving=true;
    int r=0;
    int c=0;
   
    if (!setDir(r, c, dir)) {
        ss << name << " trips and falls on their face.";
        mp->addInfo(ss.str());
        return false;
    }
     
    if (dotTime) {
        health-=dotDamage;
        dotTime--;
        ss << name << " takes " << dotDamage << " fire damage. ";
    } else {
        dotDamage=0;
        lightBonus=0;
        onFire = false;
    }
    
    Cell* cll = mp->getCell(row+r, column+c);
    Character *target = cll->getOccupant();
    if (target) {
        if (mobility && target->isTreasure()) {
            takeTreasure(cll);
        } else if (target->isPotion()) {
            string potName = takePotion(cll);
            moving = false;
            ss << name << " uses " << potName << ".";
        } else {
            attack(target);
            moving = false;
        }
    }
    
    if (moving && mobility) {
        ss << name;
        if (move(dir)) {
            ss << " moves " << getDir(dir);
            for (int i=0; i<cll->amtNeighbours(); i++) {
                Character *occ = cll->getNeighbour(i)->getOccupant();
                if (occ && occ->isPotion()) {
                    ss << " and sees an unknown potion";
                    break;
                }
            }
            ss << ".";
        } else {
            ss << " stands there like an idiot.";
            success = false;
        }
    } else if (moving && !mobility) {
        if (rand()%3>=1) {
            mobility=true;
            ss << name << " breaks free of grapple.";
        } else {
            ss << name << " fails to break free of grapple.";
        }
    }


    mp->addInfo(ss.str());
    return success;

}

