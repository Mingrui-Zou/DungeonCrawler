#ifndef __ELF_H__
#define __ELF_H__
#include <ncurses.h>
#include <iostream>
#include "player.h"

class Map;
class Cell;

class Elf: public Player {
    
    public:
    Elf(int row, int col, Map *mp);
    ~Elf();

    std::string takePotion(Cell *cll);

    void playerInfo(WINDOW *win);
};




#endif
