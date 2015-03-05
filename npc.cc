#include <cstdlib>
#include <ctime>
#include <sstream>
#include <string>
#include "gameobject.h"
#include "character.h"
#include "treasure.h"
#include "player.h"
#include "map.h"
#include "cell.h"
#include "npc.h"
using namespace std;

NPC::NPC(int row, int col, Map *mp, char sym, string name, int maxHealth, int health, int atk, int def, int dropGold, bool hostile, Player *pc):
    Character(row, col, mp, sym, name, maxHealth, health, atk, def),
    dropGold(dropGold),
    hostile(hostile),
    pc(pc) {
    string dir[8] = {"no", "so", "ea", "we", "ne", "nw", "se", "sw"};
    int randID = rand()%8;
    prevDir = dir[randID];
}

NPC::~NPC() {}

bool NPC::action() {
    
    if (health<=0) {
        drop();
        return false;   //this means it dead
    }
    
    //if player is near
    Cell *cur = mp->getCell(row, column);
    for (int i=0; i<cur->amtNeighbours(); i++) {
        Cell *adj = cur->getNeighbour(i);
        if (adj && adj->getOccupant() && adj->getOccupant()->getSym()=='@') { 
            Character *target = adj->getOccupant();
            if (hitRate>rand()%100) {
                int dmgDealt = attack(target);
            } else {
                stringstream ss;
                ss << name << " misses " << target->getName() << ".";
                mp->addInfo(ss.str());
            }
            return true;
        }
    }
    
    string dir[8] = {"no", "so", "ea", "we", "ne", "nw", "se", "sw"};
    
    if (!(rand()%3>=1 && move(prevDir))) {
        for (int i=0; i<8; i++) {
            int pos = rand()%(8-i)+i;
            
            //swaps values randomly
            string tmp = dir[pos];
            dir[pos] = dir[i];
            dir[i] = tmp;
            
            if (move(dir[i])) {
                prevDir=dir[i];
                break;
            }
        }
    }

    return true;
}

void NPC::drop() {
    int r = getRow();
    int c = getCol();
    
    Treasure *gold = new Treasure(r, c, mp, dropGold);
    Cell *cll = mp->getCell(r, c);
    cll->clearOccupant(false);
    cll->setOccupant(gold);

}
