#ifndef __WALL_H__
#define __WALL_H__
#include "cell.h"

class Map;

class Wall: public Cell {
    
    public:
        Wall(int row, int col, Map *mp, char sym);
        ~Wall();
        
        void clearOccupant(bool kill);
};

#endif
