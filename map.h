#ifndef __MAP_H__
#define __MAP_H__
#include <ncurses.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>

const int HEIGHT=25;
const int WIDTH=79;
const int NUMCHAMBERS=5;
const int SPAWNCAP=20;
const int POTCAP=10;
const int TREASURECAP=10;

class Cell;
class DisplayMap;
class Chamber;
class Player;
class NPC;
class Potion;
class Treasure;

class Map {
    static Map *instance;
    Cell ***cells;      //2D array of pointers to Cells
    Chamber *chambers[NUMCHAMBERS];
    DisplayMap *display;
    int floor, numNPC;
    bool newFloor;
    std::vector<NPC*> npcs;
    std::string actions;

    Map();
    Cell *createCell(char sym, int row, int col); //used in genMap for creation of Cells
    NPC *createNPC(Player *pc);    //starts with default position
    Potion *createPotion();
    Treasure *createTreasure();
    

    void setChamber(Cell *cll, int ID);

    static bool comp(NPC *npc1, NPC *npc2);
    static void cleanup();

    public:
    
    static Map *getInstance();
    void notify(char sym, int r, int c);
    void genMap(std::ifstream &file, Player *pc);
    void clearMap(bool restart);
    Cell* getCell(int r, int c);
    void setCell(int r, int c, Cell *cll);
    int getFloor();
    bool isNewFloor();
    void nextFloor();
    void actionNPC();
    void addInfo(std::string info);
    void actionInfo(WINDOW *win);          //prints and clears actionInfo
    void addNPC(NPC *npc);

    void displayBoard(WINDOW *win);
};

#endif
