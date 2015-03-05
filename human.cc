#include <ncurses.h>
#include <iostream>
#include <iomanip>
#include <sstream>
#include "wlinefill.h"
#include "map.h"
#include "cell.h"
#include "player.h"
#include "human.h"
using namespace std;

Human::Human(int row, int col, Map *mp):
    Player(row, col, mp, 140, 140, 20, 20), 
    scoreCarry(false) {}

Human::~Human() {}

string Human::takePotion(Cell *cll) {
    string potName = cll->getOccupant()->use(this);
    cll->clearOccupant(true);
    return potName;
}

void Human::addScore(int points) {
    score += points + points/2;
    if (scoreCarry && points%2) {
        score++;
        scoreCarry = false;
    } else {
        scoreCarry = scoreCarry || points%2;
    }
}

void Human::playerInfo(WINDOW *win) {
    stringstream s1,s2,s3,s4,s5;
    
    s1 << "Race: Human Gold: " << gold;
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

