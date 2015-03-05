#ifndef __OWLBEAR_H__
#define __OWLBEAR_H__
#include "npc.h"

class Map;
class Player;

class OwlBear: public NPC {
    
    public:
    OwlBear(int row, int col, Map *mp, Player *pc);
    ~OwlBear();

    bool action();
};



#endif
