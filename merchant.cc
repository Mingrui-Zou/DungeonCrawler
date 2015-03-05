#include <cstdlib>
#include <sstream>
#include "npc.h"
#include "cell.h"
#include "map.h"
#include "merchant.h"
using namespace std;


bool Merchant::merchantHostile=false;

Merchant::Merchant(int row, int col, Map *mp, Player *pc):
    NPC(row, col, mp, 'M', "Merchant", 30, 30, 70, 5, 4, false, pc) {}

Merchant::~Merchant() {}

int Merchant::takeDmg(int dmg) {
    merchantHostile=true;

    int newDmg = ((100*dmg)/(100+(def+defBonus))); 
    if (((100*dmg)%(100+(def+defBonus)))>0) newDmg++;
    health -= newDmg;
    
    //puts action into map for display
    stringstream ss;
    ss << "deals " << newDmg << " damage to " << name;
    if (health>0) {
        ss << " (" << health << " HP).";
    } else {
        ss << ". " << name << " is dead.";
    }
    string info = ss.str();
    mp->addInfo(info);
    
    
    return newDmg;
}

void Merchant::reset() {
    merchantHostile=false;
}

bool Merchant::action() {
    
    if (health<=0) {
        drop();
        return false;   //this means it dead
    }
    
    //if player is near
    Cell *cur = mp->getCell(row, column);
    for (int i=0; i<cur->amtNeighbours(); i++) {
        Cell *adj = cur->getNeighbour(i);
        if (merchantHostile && adj && adj->getOccupant() && adj->getOccupant()->getSym()=='@') { 
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
