#ifndef __TREASURE_H__
#define __TREASURE_H__
#include "character.h"

class Map;

class Treasure: public Character {
    protected:
    int value;

    public:
    Treasure(int row, int col, Map *mp, int value);
    virtual ~Treasure();

    virtual void killDragon();
    virtual bool isTreasure();

    int getVal();
};

#endif
