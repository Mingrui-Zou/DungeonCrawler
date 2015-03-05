#ifndef __PASSAGE_H__
#define __PASSAGE_H__
#include "cell.h"

class Map;
class GameObject;

class Passage: public Cell {
    
    public:
        Passage(int row, int col, Map *mp);
        ~Passage();

};


#endif
