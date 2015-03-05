#include <ncurses.h>

void wlinefill(WINDOW *win) {
    int y,x,Y,X;
    getyx(win,y,x);
    getmaxyx(win,Y,X);
    for (int i=0; i<X-x; i++) waddch(win,' ');
}
