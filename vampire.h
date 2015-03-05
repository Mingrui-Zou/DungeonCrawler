#ifndef __VAMPIRE_H__
#define __VAMPIRE_H__
#include "npc.h"

class Map;
class Player;

class Vampire: public NPC {
    
    public:
    Vampire(int row, int col, Map *mp, Player *pc);
    ~Vampire();

    bool action();
};

#endif
