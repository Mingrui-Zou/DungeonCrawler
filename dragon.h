#ifndef __DRAGON_H__
#define __DRAGON_H__
#include "npc.h"

class Treasure;

class Dragon: public NPC {
    
    Treasure *hoard;

    public:
    Dragon(int row, int col, Map *mp, Player *pc, Treasure *hoard);
    ~Dragon();

    bool action();
    void drop();
};



#endif
