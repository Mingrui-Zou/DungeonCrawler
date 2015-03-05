#include <cstdlib>
#include <sstream>
#include <string>
#include "phoenix.h"
#include "player.h"
#include "cell.h"
#include "map.h"
using namespace std;

Phoenix::Phoenix(int row, int col, Map *mp, Player *pc):
    NPC(row, col, mp, 'X', "Phoenix", 50, 50, 30,15, 2, true, pc),
    secondLife(false) {}

Phoenix::~Phoenix() {}

bool Phoenix::action() {
    stringstream s1,s2;


    if (health<=0) {
        if (secondLife) {
            drop();
            return false;   //this means it dead
        } else {
            s1 << name << " rises from the ashes.";
            mp->addInfo(s1.str());
            secondLife=true;
            health=50;
            atkBonus=10;
        }

    }
    
    //if player is near
    Cell *cur = mp->getCell(row, column);
    for (int i=0; i<cur->amtNeighbours(); i++) {
        Cell *adj = cur->getNeighbour(i);
        if (adj && adj->getOccupant() && adj->getOccupant()->getSym()=='@') { 
            Character *target = adj->getOccupant();
            if (hitRate>rand()%100) {
                int dmgDealt = attack(target);
                target->setDot(2,7,true);
            } else {
                s2 << name << " misses " << target->getName() << ".";
                mp->addInfo(s2.str());
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
