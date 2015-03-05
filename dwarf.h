#ifndef __DWARF_H__
#define __DWARF_H__
#include <ncurses.h>
#include <string>
#include "player.h"

class Map;
class Cell;

class Dwarf: public Player {
    
    public:
    Dwarf(int row, int col, Map *mp);
    ~Dwarf();
    int takeTreasure(Cell *cll);
    std::string takePotion(Cell *cll);
    
    void playerInfo(WINDOW *win);
};



#endif
