#include <ncurses.h>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>
#include "wlinefill.h"
#include "map.h"
#include "gameobject.h"
#include "character.h"
#include "player.h"
#include "human.h"
#include "elf.h"
#include "dwarf.h"
#include "ork.h"
#include "cell.h"
using namespace std;

static void finish(int sig);

bool chstr(WINDOW *win, string &s);

int main(int argc, char *argv[]) {
    
    initscr();
    
    start_color();
    init_pair(1, COLOR_YELLOW, COLOR_RED);
    init_pair(2, COLOR_RED, COLOR_YELLOW);


    cbreak();
    noecho();
    keypad(stdscr, true);

    WINDOW *win = newwin(33,79,0,0);
    scrollok(win,false);
        
    wattron(win, A_BOLD);

    srand(time(NULL));  //1406223664
    bool done=false;
    while (!done) {
        
        ifstream floorList("levels/floorLst1.txt");
        
        //if (argc==2) ifstream floorList(argv[1]);
        
        string s;
        stringstream ss;
        char ch;
        Map *mainMap;
        vector<string> allFloors;

        while (floorList>>s) {
            allFloors.push_back(s);
        }

        for (int i=0; i<allFloors.size(); i++) {
            int randID = rand()%(allFloors.size()-i)+i;

            string temp = allFloors[randID];
            allFloors[randID] = allFloors[i];
            allFloors[i] = temp;
        }

        if (allFloors.size()>0) { 
            ifstream floor1(allFloors[0].c_str());
            mainMap = Map::getInstance();
            
            do {
                werase(win);
                mvwaddstr(win,12,20,"Select race: (h)uman (e)lf (d)warf (o)rk");
                wrefresh(win);
                ch=wgetch(win);
            } while (ch!='h' && ch!='e' && ch!='d' && ch!='o' && ch!='Q');
            
            // generates player race
            //initial position doesn't matter, position changes during generation
            Player *pc;
            if (ch=='e') pc = new Elf(0, 0, mainMap);
            else if (ch=='d') pc = new Dwarf(0, 0, mainMap);
            else if (ch=='o') pc = new Ork(0, 0, mainMap);
            else pc = new Human(0, 0, mainMap); 

            mainMap->genMap(floor1,pc);

            mainMap->displayBoard(win);
            pc->playerInfo(win);
            mainMap->actionInfo(win);
            wrefresh(win);
            
            if (ch=='Q') s="q";

            while (s!="q" && s!="r" && chstr(win,s) && s!="q" && s!="r") {
                while (s!="q" && s!="r" && !pc->action(s)) {
                    mainMap->displayBoard(win);
                    pc->playerInfo(win);
                    mainMap->actionInfo(win);
                    wrefresh(win);
                    chstr(win,s);
                }
                
                if (s=="q" || s=="r") break;

                if (mainMap->isNewFloor() && mainMap->getFloor()<=5) {
                    mainMap->clearMap(false);
                    ifstream nextFloor(allFloors[mainMap->getFloor()-1].c_str());
                    mainMap->genMap(nextFloor,pc);
                } else if (mainMap->isNewFloor()) {
                    done = true;
                    delete pc;
                    break;  //no more floors in floorList
                } else {    
                    mainMap->actionNPC();
                }
                
                mainMap->displayBoard(win);
                pc->playerInfo(win);
                mainMap->actionInfo(win);
                wrefresh(win);

                //checks if player dead
                if (pc->getHealth()<=0) {
                    chstr(win,s);
                    break; 
                }
                

            }

            ss << "Score: " << pc->getScore();
            werase(win);
            mvwaddstr(win,11,35,(ss.str()).c_str());
            wrefresh(win);
            
            do {
                mvwaddstr(win,12,29,"(Q)uit or (R)estart");
                wrefresh(win);
                chstr(win,s);
            } while (s!="q" && s!="r");

            if (s=="q") {
                done=true;
            } else if (s=="r") {
                done=false;
            }
            
           
            mainMap->clearMap(true);
        
        } else {
            done=true;
        }
    }
    
    finish(0);
}

static void finish(int sig) {
    endwin();

    exit(0);
}

bool chstr(WINDOW *win, string &s) {
    char c;
    if (c=wgetch(win)) {
        if (c=='Q') s="q";
        else if (c=='R') s="r";
        else if (c=='w') s="no";
        else if (c=='s') s="so";
        else if (c=='a') s="we";
        else if (c=='d') s="ea";
        else if (c=='q') s="nw";
        else if (c=='e') s="ne";
        else if (c=='z') s="sw";
        else if (c=='c') s="se";
        else s="nope";

        return true;
    }
    return false;
}





