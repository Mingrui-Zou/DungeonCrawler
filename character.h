#ifndef __CHARACTER_H__
#define __CHARACTER_H__
#include <string>
#include "gameobject.h"

class Map;
class Player;
class Human;
class Elf;
class Dwarf;
class Ork;
//class Druid;

class Character: public GameObject {
    protected:
    int maxHealth, health, atk, atkBonus, def, defBonus, hitRate, hitRateBonus, light, lightBonus, dotDamage, dotTime;
    bool mobility, onFire;


    Character(int row, int col, Map *mp, char sym, std::string name, int maxHealth, int health, int atk, int def);
    
    public:
    virtual ~Character();
    
    virtual void setDot(int damage, int time, bool isFire);
    virtual bool isOnFire();

    virtual void setMobility(bool canMove);
    virtual bool isMobile();

    virtual int subGold(int amt);

    virtual bool isTreasure();
    virtual int getVal();
    
    virtual bool isPotion();
    virtual std::string use(Human *pc);
    virtual std::string use(Elf *pc);
    virtual std::string use(Dwarf *pc);
    virtual std::string use(Ork *pc);
    //virtual std::string use(Druid *pc);

    virtual void addAtk(int boost);
    virtual void addDef(int boost);
    virtual void resHealth(int res);
    virtual void resetBoosts();

    virtual int takeDmg(int dmg);
    virtual bool move(std::string dir);
    virtual int attack(Character *target);

    int getLight();
    int getHealth();
};

#endif
