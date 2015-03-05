#ifndef __WEREWOLF_H__
#define __WEREWOLF_H__
#include "npc.h"

class Map;
class Player;

class Werewolf: public NPC {
    
    public:
    Werewolf(int row, int col, Map *mp, Player *pc);
    ~Werewolf();

    bool action();
};



#endif
