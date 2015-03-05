#include <ncurses.h>
#include <ctime>
#include <cstdlib>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include "wlinefill.h"
#include "cell.h"
    #include "chamber.h"
    #include "stair.h"
    #include "floor.h"
    #include "wall.h"
    #include "door.h"
    #include "passage.h"
#include "character.h"
#include "player.h"
#include "npc.h"
    #include "goblin.h"
    #include "vampire.h"
    #include "werewolf.h"
    #include "troll.h"
    #include "phoenix.h"
    #include "merchant.h"
    #include "owlbear.h"
#include "potion.h"
    #include "restorehealth.h"
    #include "poison.h"
    #include "boostatk.h"
    #include "boostdef.h"
    #include "woundatk.h"
    #include "wounddef.h"
#include "treasure.h"
    #include "dragonhoard.h"
#include "map.h"
#include "displaymap.h"
using namespace std;

Map *Map::instance=NULL;

Map::Map(): floor(1), numNPC(0), newFloor(false), actions("Action: ") {
    cells = new Cell**[HEIGHT];
    for (int i=0; i<HEIGHT; i++) cells[i] = new Cell*[WIDTH];
    display = new DisplayMap(HEIGHT, WIDTH);
    npcs.reserve(1);
}

Cell *Map::createCell(char sym, int row, int col) {
    Cell *temp=NULL;
    
    if (sym=='.') {                                     //floor
        temp = new Floor(row, col, this);
    } else if (sym=='-' || sym=='|' || sym==' ') {                       //wall
        temp = new Wall(row, col, this, sym);
    } else if (sym=='+') {
        temp = new Door(row, col, this);
    } else if (sym=='#') {
        temp = new Passage(row, col, this);
    } else {
        cerr << "Invalid Char in createCell" << endl;
    }

    return temp;
}

NPC *Map::createNPC(Player *pc) {
    int randID = rand()%100;
    NPC *npc;

    if (randID<20) npc = new Goblin(0,0,this,pc);
    else if (randID<35) npc = new Werewolf(0,0,this,pc);
    else if (randID<50) npc = new Vampire(0,0,this,pc);
    else if (randID<60) npc = new Troll(0,0,this,pc);
    else if (randID<75) npc = new Phoenix(0,0,this,pc);
    else if (randID<85) npc = new Merchant(0,0,this,pc);
    else npc = new OwlBear(0,0,this,pc);

    return npc;
}

Potion *Map::createPotion() {
    int randID = rand()%6;
    Potion *potion;

    if (randID==0) potion = new RestoreHealth(0, 0, this);
    else if (randID==1) potion = new Poison(0, 0, this);
    else if (randID==2) potion = new BoostAtk(0, 0, this);
    else if (randID==3) potion = new WoundAtk(0, 0, this);
    else if (randID==4) potion = new BoostDef(0, 0, this);
    else potion = new WoundDef(0, 0, this);
    
    return potion;
}

Treasure *Map::createTreasure() {
    int randID=rand()%8;
    Treasure *gold;
    
    if (randID==0) gold = new DragonHoard(0,0,this);
    else if (randID>=1 && randID<3) gold = new Treasure(0,0,this,1);
    else gold = new Treasure(0,0,this,2);

    return gold;
}

void Map::cleanup() {
    for (int i=0; i<HEIGHT; i++) {
        for (int j=0; j<WIDTH; j++) {
            if (instance->cells[i][j]) delete instance->cells[i][j];
        }
        delete [] instance->cells[i];
    }
    delete [] instance->cells;
    delete instance->display;
    delete instance;
}

void Map::clearMap(bool restart) {
    if (restart) {
        floor=1;
        Merchant::reset();
    }
    for (int i=0; i<NUMCHAMBERS; i++) delete chambers[i];
    for (int i=0; i<HEIGHT; i++) {
        for (int j=0; j<WIDTH; j++) {
            if (cells[i][j]) delete cells[i][j];
            cells[i][j]=NULL;
        }
    }
    npcs.clear();
    numNPC = 0;
    newFloor = false;
}

Map *Map::getInstance() {
    if (!instance) {
        instance = new Map;
        atexit(cleanup);
    }
    return instance;
}

void Map::notify(char sym, int r, int c) {
    display->notify(sym, r, c);
}

void Map::genMap(ifstream &file, Player *pc) {
    pc->resetBoosts();

    //reads in map
    display->addPC(pc);
    for (int i=0; i<HEIGHT; i++) {
        string line;
        getline(file, line);
        if (!file.eof()) {
            int len = line.length();
            for (int j=0; j<WIDTH; j++) {
                char sym;
                if (j<len) sym = line[j];
                else sym = ' ';
                cells[i][j] = createCell(sym, i, j);
                display->notify(sym, i, j);
            }
        } else {
            for (int j=0; j<WIDTH; j++) {
                cells[i][j] = createCell(' ', i, j);
                display->notify(' ', i, j);
            }
        }
    }
    
    //sets up neighbours
    for (int i=0; i<HEIGHT; i++) {
        for (int j=0; j<WIDTH; j++) {
            //cardinal neighbours
            if (i > 0) cells[i][j]->addNeighbour(cells[i-1][j]);
            if (i < HEIGHT-1) cells[i][j]->addNeighbour(cells[i+1][j]);
            if (j > 0) cells[i][j]->addNeighbour(cells[i][j-1]);
            if (j < WIDTH-1) cells[i][j]->addNeighbour(cells[i][j+1]);
            
            //diagonal neighbours
            if (i>0 && j>0) cells[i][j]->addNeighbour(cells[i-1][j-1]);                  
            if (i>0 && j<WIDTH-1) cells[i][j]->addNeighbour(cells[i-1][j+1]);
            if (i<HEIGHT-1 && j>0) cells[i][j]->addNeighbour(cells[i+1][j-1]);
            if (i<HEIGHT-1 && j<WIDTH-1) cells[i][j]->addNeighbour(cells[i+1][j+1]);            
        }
    }

    

    //partitions cells into chambers
    for (int i=0; i<NUMCHAMBERS; i++) chambers[i] = new Chamber(i+1); 
    
    int ID = 0;
    for (int i=0; i<HEIGHT; i++) {
        for (int j=0; j<WIDTH; j++) {
            if (!cells[i][j]->getCID()) {
                ID++;
                setChamber(cells[i][j], ID); //sets entire chamber
            }
        }
    }

    //spawns player
    int pcChamber = rand()%NUMCHAMBERS;
    if (!chambers[pcChamber]->spawn(pc)) cerr << "WTF something wrong with chamber spawning player" << endl;
    addInfo("Player character has spawned.");


    //spawns stair
    Cell *stair = new Stair(0, 0, this);
    int stairChamber;
    do {
        stairChamber = rand()%NUMCHAMBERS;
    } while (stairChamber==pcChamber);

    if (!chambers[stairChamber]->spawn(stair, this)) cerr << "WTF something wrong with spawning stair" << endl;

    //spawn potion
    for (int i=0; i<POTCAP; i++) {
        Potion *potion = createPotion();
        int potChamber = rand()%NUMCHAMBERS;
        bool spawned = chambers[potChamber]->spawn(potion);
        while (!spawned) {
            potChamber = rand()%NUMCHAMBERS;
            spawned = chambers[potChamber]->spawn(potion);
        }
    }

    //spawn treasure
    for (int i=0; i<TREASURECAP; i++) {
       Treasure *gold = createTreasure();
       int goldChamber = rand()%NUMCHAMBERS;
       bool spawned = chambers[goldChamber]->spawn(gold,this,pc);
       while(!spawned) {
           goldChamber = rand()%NUMCHAMBERS;
           spawned = chambers[goldChamber]->spawn(gold,this,pc);
       }
    }

    //spawn enemies, werewolves for now
    for (int i=0; i<SPAWNCAP; i++) {
        //have a thing here to determine which npc to spawn

        NPC *npc = createNPC(pc);
        addNPC(npc);

        int npcChamber = rand()%NUMCHAMBERS;
        bool spawned = chambers[npcChamber]->spawn(npc);
        while (!spawned) {
            npcChamber = rand()%NUMCHAMBERS;
            spawned = chambers[npcChamber]->spawn(npc);
        }

    }

}

void Map::setChamber(Cell *cll, int ID) {
        cll->setCID(ID);
        chambers[ID-1]->addCell(cll);
        for (int i=0; i<cll->amtNeighbours(); i++) {
            if (!cll->getNeighbour(i)->getCID()) {
                setChamber(cll->getNeighbour(i), ID);
            }
        }
}

Cell *Map::getCell(int r, int c) {
    return cells[r][c];
}

//Does not delete cell already there
void Map::setCell(int r, int c, Cell *cll) {
    cells[r][c] = cll;

}

int Map::getFloor() {
    return floor;
}

bool Map::isNewFloor() {
    return newFloor;
}

void Map::nextFloor() {
    newFloor = true;
    floor++;
}

bool Map::comp(NPC *npc1, NPC *npc2) {
    if (!npc1) return false;
    if (!npc2) return true;
    
    int r1 = npc1->getRow();
    int r2 = npc2->getRow();
    int c1 = npc1->getCol();
    int c2 = npc2->getCol();
    return ((r1<r2) || ((r1==r2) && (c1<c2)));
}

void Map::actionNPC() {
    sort(npcs.begin(), npcs.end(), comp);
    

    for (int i=numNPC-1; i>=0; i--) {
        if (!npcs[i]) {
            npcs.erase(npcs.begin()+i);
            numNPC--;
        }
    }

    for (int i=0; i<numNPC; i++) {
        int r = npcs[i]->getRow();
        int c = npcs[i]->getCol();
        if (!npcs[i]->action()) {
            delete npcs[i];
            npcs[i]=NULL;
        }
    }
}

void Map::addInfo(string info) {
    actions += " ";
    actions += info;
}

void Map::actionInfo(WINDOW *win) {    
    int y,x,Y,X;
    getmaxyx(win,Y,X);
    
    mvwaddstr(win,29,0,actions.c_str());
    getyx(win,y,x); 
    wlinefill(win);
    
    for (int i=1; i<=Y-y; i++) {
        wmove(win,y+i,0);
        wclrtoeol(win);
    }

    actions = "Action:";
}

void Map::addNPC(NPC *npc) {
    npcs.push_back(npc);
    numNPC++;
}

void Map::displayBoard(WINDOW *win) {
    display->displayBoard(win);
}
