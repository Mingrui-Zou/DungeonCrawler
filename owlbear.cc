#include <cstdlib>
#include <iostream>
#include <sstream>
#include <string>
#include "map.h"
#include "cell.h"
#include "character.h"
#include "player.h"
#include "owlbear.h"
using namespace std;

OwlBear::OwlBear(int row, int col, Map *mp, Player *pc):
    NPC(row, col, mp, 'O', "OwlBear", 100, 100, 20, 10, 1, true, pc) {}

OwlBear::~OwlBear() {}

bool OwlBear::action() {
    
    stringstream ss;
    
    if (health<=0) {
        pc->setMobility(true);
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
                if (target->isMobile()) {               
                    ss << name << " grapples " << target->getName() << ".";
                    target->setMobility(false);
                }
            } else {
                ss << name << " misses " << target->getName() << ".";
            }
            mp->addInfo(ss.str());
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
