#include <cstdlib>
#include <sstream>
#include <string>
#include "troll.h"
#include "player.h"
#include "map.h"
#include "cell.h"
using namespace std;

Troll::Troll(int row, int col, Map *mp, Player *pc):
    NPC(row, col, mp, 'T', "Troll", 120, 60, 25, 15, 1, true, pc) {}

Troll::~Troll() {}

bool Troll::action() {
    
    resHealth(5);

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
