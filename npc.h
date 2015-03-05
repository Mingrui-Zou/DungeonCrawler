#ifndef __NPC_H__
#define __NPC_H__
#include <string>
#include "character.h"

class Player;
class Map;

class NPC: public Character {
    protected:
    int dropGold;
    bool hostile;
    std::string prevDir;
    Player *pc;

    NPC(int row, int col, Map *mp, char sym, std::string name, int maxHealth, int health, int atk, int def, int dropGold, bool hostile, Player *pc);
    
    public:
    virtual ~NPC();

    virtual bool action(); //returns false if health is zero
    virtual void drop(); //kills npc and drops loot
};

#endif
