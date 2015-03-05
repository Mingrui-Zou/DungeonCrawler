#include <string>
#include <cstdlib>
#include <sstream>
#include "cell.h"
#include "werewolf.h"
#include "player.h"
#include "map.h"
using namespace std;


Werewolf::Werewolf(int row, int col, Map *mp, Player *pc):
    NPC(row, col, mp, 'W', "Were-Wolf", 120, 120, 30, 5, 1, true, pc) {}

Werewolf::~Werewolf() {}

bool Werewolf::action() {
    
    if (health<=0) {
        drop();
        return false;   //this means it dead
    }
    
    //if player is near
    Cell *cur = mp->getCell(row, column);
    
    string enemies[2]={"Vampire","PC"};
    
    for (int i=0; i<2; i++) {
        for (int j=0; j<cur->amtNeighbours(); j++) {
            Cell *adj = cur->getNeighbour(j);
            if (adj && adj->getOccupant()) {
                Character *target = adj->getOccupant();
                if (target->getName()==enemies[i]) {
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
