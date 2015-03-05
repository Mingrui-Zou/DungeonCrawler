#ifndef __DISPLAYMAP_H__
#define __DISPLAYMAP_H__
#include <iostream>
#include <ncurses.h>

class Map;
class Player;

class DisplayMap;

class DisplayMap {
    int h, w;
    char **display;
    bool playerBlink;
    Player *pc;

    public:
    DisplayMap(int h, int w);
    ~DisplayMap();

    void notify(char sym, int r, int c);
    void addPC(Player *newpc);

    void displayBoard(WINDOW *win);
};

#endif
