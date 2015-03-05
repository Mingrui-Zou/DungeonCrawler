#ifndef __PHOENIX_H__
#define __PHOENIX_H__
#include "npc.h"

class Map;
class Player;

class Phoenix: public NPC {

    bool secondLife;

    public:
    Phoenix(int row, int col, Map *mp, Player *pc);
    ~Phoenix();

    bool action();
    
};




#endif
