#include <vector>
#include <iostream>
#include <cstdlib>
#include <string>
#include "player.h"
#include "npc.h"
#include "potion.h"
#include "treasure.h"
#include "dragonhoard.h"
#include "dragon.h"
#include "chamber.h"
#include "cell.h"
#include "map.h"
using namespace std;

Chamber::Chamber(int ID): ID(ID), numObjects(0), numCells(0) {
    cells.reserve(1);
}

Chamber::~Chamber() {}

int Chamber::getID() {
    return ID;
}

int Chamber::getNumObjects() {
    return numObjects;
}

int Chamber::getNumCells() {
    return numCells;
}

void Chamber::addCell(Cell *cll) {
    cells.push_back(cll);
    numCells++;
}

void Chamber::swap(int a, int b) {
    Cell *tmp = cells[b];
    cells[b] = cells[a];
    cells[a] = tmp;
}

bool Chamber::spawn(Player *pc) {
    int pos = rand()%(numCells-numObjects)+numObjects;
    
    swap(numObjects, pos);

    if (cells[numObjects]->setOccupant(pc)) {
        numObjects++;
        return true;
    } else {
        return false;
    }
}

bool Chamber::spawn(NPC *npc) {
    int pos = rand()%(numCells-numObjects)+numObjects;
    
    swap(numObjects, pos);

    if (cells[numObjects]->setOccupant(npc)) {
        numObjects++;
        return true;
    } else {
        return false;
    }
}

bool Chamber::spawn(Potion *potion) {
    int pos = rand()%(numCells-numObjects)+numObjects;
    
    swap(numObjects, pos);

    if (cells[numObjects]->setOccupant(potion)) {
        numObjects++;
        return true;
    } else {
        return false;
    }
}

bool Chamber::spawn(Treasure *gold, Map *mp, Player *pc) {
    int pos = rand()%(numCells-numObjects)+numObjects;

    if (gold->getVal()==DRAGONHOARDVALUE) {
        bool valid=false;
        Dragon* drgn = new Dragon(0,0,mp,pc,gold);
        do {
            pos = rand()%(numCells-numObjects)+numObjects;

            //random position for dragon
            int max = cells[pos]->amtNeighbours();
            int numbers[max];
            for (int i=0; i<max; i++) numbers[i]=i;
            for (int i=0; i<max; i++) {
                int randID = rand()%(max-i)+i;
                int temp = numbers[randID];
                numbers[randID] = numbers[i];
                numbers[i] = temp;
            }

            for (int i=0; i<cells[pos]->amtNeighbours(); i++) {
                if (cells[pos]->getNeighbour(numbers[i])->setOccupant(drgn)) {
                    mp->addNPC(drgn);
                    valid = true;
                    break;
                }
            }

        } while (!valid);

        for (int i=numObjects; i<numCells; i++) {
            if (cells[i]->getOccupant() && cells[i]->getOccupant()->getName()=="Dragon") {
                swap(numObjects, i);
                numObjects++;
                break;
            }
        }
           
    }


    swap(numObjects, pos);

    if (cells[numObjects]->setOccupant(gold)) {
        numObjects++;
        return true;
    } else {
        return false;
    }
}

bool Chamber::spawn(Cell *stair, Map* mp) {
    int pos = rand()%numCells;

    swap(numCells-1, pos);    //switch with last
     
    int r = cells[numCells-1]->getRow();
    int c = cells[numCells-1]->getCol();
    stair->setRow(r);
    stair->setCol(c);
    Cell *temp = mp->getCell(r,c);
    mp->setCell(r, c, stair);
    cells.erase(cells.begin()+numCells-1);
    numCells--;

    //update neighbours

    for (int i=0; i<temp->amtNeighbours(); i++) {
        if (!temp->getNeighbour(i)->replaceNeighbour(stair)) {
            cerr << "WTF something wrong with replace neighbour in spawn stair" << endl;
        }
    }
    delete temp;

    stair->notifyMap();

    return true;
}
