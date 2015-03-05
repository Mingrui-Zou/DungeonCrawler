#ifndef __HUMAN_H__
#define __HUMAN_H__
#include <ncurses.h>
#include <iostream>
#include "player.h"

class Map;
class Cell;

class Human: public Player {
    bool scoreCarry;

    public:
    Human(int row, int col, Map *mp);
    ~Human();
    
    std::string takePotion(Cell *cll);

    void addScore(int points);
    
    void playerInfo(WINDOW *win);
};


#endif
