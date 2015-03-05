#include <iostream>
#include <sstream>
#include <string>
#include "cell.h"
#include "character.h"
#include "map.h"
using namespace std;

Character::Character(int row, int col, Map *mp, char sym, string name, int maxHealth, int health, int atk, int def): 
    GameObject(row, col, mp, sym, name), 
    maxHealth(maxHealth), 
    health(health), 
    atk(atk), 
    def(def),
    atkBonus(0),
    defBonus(0),
    hitRate(50),
    light(5), 
    lightBonus(0),
    dotDamage(0),
    dotTime(0),
    mobility(true),
    onFire(false) {}

Character::~Character() {}

void Character::setDot(int damage, int time, bool isFire) {
    dotTime = time;
    dotDamage = damage;
    if (isFire) {
        lightBonus=5;
        onFire = true;
    }
}

bool Character::isOnFire() {
    return onFire;
}

bool Character::isMobile() {
    return mobility;
}

void Character::setMobility(bool canMove) {
    mobility=canMove;
}

int Character::subGold(int amt) {
    return 0;
}

bool Character::isTreasure() {
    return false;
}

int Character::getVal() {
    return 0;
}

bool Character::isPotion() {
    return false;
}

string Character::use(Human *pc) { return ""; }
string Character::use(Elf *pc) { return ""; }
string Character::use(Dwarf *pc) { return ""; }
string Character::use(Ork *pc) { return ""; }
//string Character::use(Druid *pc) { return ""; }


void Character::addAtk(int boost) {
    atkBonus += boost;
    if (atk+atkBonus<0) {
        atkBonus = atk;
    }
}

void Character::addDef(int boost) {
    defBonus += boost;
    if (def+defBonus<0) {
        defBonus = def;
    }
}

void Character::resHealth(int res) {
    health += res;
    if (health<1) {
        health=1;
    } else if (health > maxHealth) {
        health=maxHealth;
    }
}

void Character::resetBoosts() {
    atkBonus=0;
    defBonus=0;
    lightBonus=0;
}

int Character::takeDmg(int dmg) {
    int newDmg = ((100*dmg)/(100+(def+defBonus))); 
    if (((100*dmg)%(100+(def+defBonus)))>0) newDmg++;
    health -= newDmg;
    
    //puts action into map for display
    stringstream ss;
    ss << "deals " << newDmg << " damage to " << name;
    if (health>0) {
        ss << " (" << health << " HP).";
    } else {
        ss << ". " << name << " is dead.";
    }
    string info = ss.str();
    mp->addInfo(info);
    
    
    return newDmg;
}

int Character::attack(Character *target) {
        
        stringstream ss;
        ss << name;
        string info = ss.str();
        mp->addInfo(info);

        int dmg = target->takeDmg(atk+atkBonus);
        return dmg;
}

bool Character::move(string dir) {
    int r=0;
    int c=0; 
    if (!setDir(r, c, dir)) cerr << "Invalid direction" << endl;
    
    if (mp->getCell(row+r, column+c)->setOccupant(this)) {
        mp->getCell(row-r,column-c)->clearOccupant(false); //set occupant makes row, col into row+r and col+c
        return true;
    } else {
        return false;
    }
}

int Character::getLight() {
    return (light + lightBonus);
}

int Character::getHealth() {
    return health;
}
