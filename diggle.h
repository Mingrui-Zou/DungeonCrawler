#ifndef __DIGGLE_H__
#define __DIGGLE_H__
#include "npc.h"

class Diggle: public NPC {

    public:
    Diggle(int row, int col, Map *mp, Player *pc);
    ~Diggle();

    bool action();
    void drop();

};



#endif
