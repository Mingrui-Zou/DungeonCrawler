#include <iostream>
#include <ncurses.h>
#include "map.h"
#include "character.h"
#include "player.h"
#include "displaymap.h"
using namespace std;

DisplayMap::DisplayMap(int h, int w): h(h), w(w), playerBlink(false), pc(NULL) {
    display = new char*[h];
    for (int i=0; i<h; i++) display[i] = new char[w];
}

DisplayMap::~DisplayMap() {
    for (int i=0; i<h; i++) delete [] display[i];
    delete [] display;
}

void DisplayMap::notify(char sym, int r, int c) {
    display[r][c] = sym;
}

void DisplayMap::addPC(Player *newpc) {
    pc = newpc;
}

void DisplayMap::displayBoard(WINDOW *win) {
    int r,c,l;
    
    if (pc) {
        r=pc->getRow();
        c=pc->getCol();
        l=pc->getLight();
    }
   
    for (int i=0; i<h; i++) {
        wmove(win,i,0);
        for (int j=0; j<w; j++) {
            if (pc && i<=r+l && i>=r-l && j<=c+l && j>=c-l) {
                if (i==r && j==c && pc->isOnFire()) { 
                    if (playerBlink) wattron(win, COLOR_PAIR(1));
                    else wattron(win, COLOR_PAIR(2));
                }
                waddch(win, display[i][j]);
                if (i==r && j==c && pc->isOnFire()) {
                    if (playerBlink) wattroff(win, COLOR_PAIR(1));
                    else wattroff(win, COLOR_PAIR(2));
                    playerBlink = !playerBlink;
                }

            } else {
                waddch(win, '~');
            }
        }
    }

    
}
