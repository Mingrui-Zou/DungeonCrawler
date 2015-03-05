#ifndef __STAIR_H__
#define __STAIR_H__
#include "cell.h"

class Map;

class Stair: public Cell {
    
    public:
    Stair(int row, int col, Map *mp);
    ~Stair();

    bool setOccupant(Character *target);
};

#endif
