#ifndef __GOBLIN_H__
#define __GOBLIN_H__
#include "npc.h"

const int STLMAX = 3;
const int STLMIN = 1;

class Map;
class Player;

class Goblin: public NPC {
    
    public:
    Goblin(int row, int col, Map *mp, Player *pc);
    ~Goblin();

    bool action();
};




#endif
