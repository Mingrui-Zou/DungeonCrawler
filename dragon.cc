#include <cstdlib>
#include <iostream>
#include <sstream>
#include <string>
#include "map.h"
#include "cell.h"
#include "treasure.h"
#include "character.h"
#include "dragon.h"
using namespace std;

Dragon::Dragon(int row, int col, Map *mp, Player *pc, Treasure *hoard):
    NPC(row, col, mp, 'D', "Dragon", 150, 150, 20, 20, 0, true, pc),
    hoard(hoard) {}

Dragon::~Dragon() {}    

bool Dragon::action() {
    
    if (health<=0) {
        drop();
        hoard->killDragon();
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
        }
    }

    return true;
}

void Dragon::drop() {
    int r = getRow();
    int c = getCol();

    Cell *cll = mp->getCell(r, c);
    cll->clearOccupant(false);
}
