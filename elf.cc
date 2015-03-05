#include <iostream>
#include <iomanip>
#include <ncurses.h>
#include <sstream>
#include "wlinefill.h"
#include "map.h"
#include "cell.h"
#include "player.h"
#include "elf.h"
using namespace std;

Elf::Elf(int row, int col, Map *mp):
    Player(row, col, mp, 140, 140, 30, 10) {}

Elf::~Elf() {}

string Elf::takePotion(Cell *cll) {
    string potName = cll->getOccupant()->use(this);
    cll->clearOccupant(true);
    return potName;
}

void Elf::playerInfo(WINDOW *win) {
    stringstream s1,s2,s3,s4,s5;
    
    s1 << "Race: Elf Gold: " << gold;
    mvwaddstr(win,25,0,(s1.str()).c_str());

    s2 << "Floor " << mp->getFloor();
    mvwaddstr(win,25,68,(s2.str()).c_str());
    wlinefill(win);
    
    if (health<0) health=0;
    s3 << "HP: " << health;
    mvwaddstr(win,26,0,(s3.str()).c_str());
    wlinefill(win);

    s4 << "Atk: " << atk+atkBonus;
    mvwaddstr(win,27,0,(s4.str()).c_str());
    wlinefill(win);
        
    s5 << "Def: " << def+defBonus;
    mvwaddstr(win,28,0,(s5.str()).c_str());
    wlinefill(win);
}

