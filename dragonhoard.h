#ifndef __DRAGONHOARD_H__
#define __DRAGONHOARD_H__
#include "treasure.h"

const int DRAGONHOARDVALUE=6;

class Map;
class Dragon;

class DragonHoard: public Treasure {
    
    bool dragonAlive;

    public:
    DragonHoard(int row, int col, Map *mp);  
    ~DragonHoard();
    void killDragon();

    bool isTreasure();      //determines whether player can take it    
};



#endif
