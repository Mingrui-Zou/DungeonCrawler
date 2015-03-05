#ifndef __ORK_H__
#define __ORK_H__
#include <ncurses.h>
#include <string>
#include "player.h"

class Map;
class Cell;

class Ork: public Player {

    bool goldCarry;

    public:
    Ork(int row, int col, Map *mp);
    ~Ork();
    
    int takeTreasure(Cell *cll);
    std::string takePotion(Cell *cll);

    void playerInfo(WINDOW *win);
};



#endif
