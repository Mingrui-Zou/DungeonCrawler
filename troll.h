#ifndef __TROLL_H__
#define __TROLL_H__
#include "npc.h"

class Map;
class Player;

class Troll: public NPC {
    
    public:
    Troll(int row, int col, Map *mp, Player *pc);
    ~Troll();
    
    bool action();

};



#endif
