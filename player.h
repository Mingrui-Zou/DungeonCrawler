#ifndef __PLAYER_H__
#define __PLAYER_H__
#include <ncurses.h>
#include <string>
#include <iostream>
#include "character.h"

class Cell;

class Player: public Character {
    protected:

    int gold, score;

    Player(int row, int col, Map *mp, int maxHealth, int health, int atk, int def);
    
    public:
    virtual ~Player();
    virtual int takeTreasure(Cell *cll);
    virtual void addScore(int points);
    int getScore();
    virtual bool action(std::string dir);
    int subGold(int amt);

    virtual std::string takePotion(Cell *cll)=0;
    
    virtual void playerInfo(WINDOW *win)=0;
};



#endif
