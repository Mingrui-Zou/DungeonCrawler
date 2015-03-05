#include <iostream>
#include <iomanip>
#include <ncurses.h>
#include <sstream>
#include "wlinefill.h"
#include "map.h"
#include "cell.h"
#include "player.h"
#include "dwarf.h"
using namespace std;

Dwarf::Dwarf(int row, int col, Map *mp):
    Player(row, col, mp, 100, 100, 20, 30) {}

Dwarf::~Dwarf() {}


int Dwarf::takeTreasure(Cell *cll) {
    int amt = cll->getOccupant()->getVal();
    gold += 2*amt;
    addScore(2*amt);

    cll->clearOccupant(true);

    return amt;
}

string Dwarf::takePotion(Cell *cll) {
    string potName = cll->getOccupant()->use(this);
    cll->clearOccupant(true);
    return potName;
}

void Dwarf::playerInfo(WINDOW *win) {
    stringstream s1,s2,s3,s4,s5;
    
    s1 << "Race: Dwarf Gold: " << gold;
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
