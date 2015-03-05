#ifndef __MERCHANT_H__
#define __MERCHANT_H__
#include "npc.h"

class Map;
class Player;

class Merchant: public NPC {
    static bool merchantHostile;

    public:
    Merchant(int row, int col, Map *mp, Player *pc);
    ~Merchant();

    int takeDmg(int dmg);
    static void reset();

    bool action();

};




#endif
