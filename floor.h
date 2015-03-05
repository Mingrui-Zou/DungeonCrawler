#ifndef __FLOOR_H__
#define __FLOOR_H__
#include "cell.h"

class Map;

class Floor: public Cell {

    public:
        Floor(int row, int col, Map *mp);
        ~Floor();
};

#endif
