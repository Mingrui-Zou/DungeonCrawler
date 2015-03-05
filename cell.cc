#include <cstdlib>
#include <string>
#include "map.h"
#include "cell.h"
#include "character.h"
#include "gameobject.h"
using namespace std;

Cell::Cell(int r, int c, Map *mp, char sym, string name, bool occ, int CID): 
    GameObject(r, c, mp, sym, name), 
    occupied(occ), 
    occupant(NULL), 
    numNeighbours(0), 
    chamberID(CID) {}

Cell::~Cell() {
    if (occupant) delete occupant;    
}

bool Cell::isOccupied() {
    return occupied;
}

Character *Cell::getOccupant() {
    return occupant;
}

bool Cell::setOccupant(Character *target) {
    if (!occupied) {
        occupant = target;      //occupant is NULL if !occupied
        target->setRow(row);
        target->setCol(column);
        occupied = true;
        mp->notify(occupant->getSym(), row, column);
        return true;            //Occupant successfully set
    } else {
        return false;           //Occupant not set
    }
}

void Cell::clearOccupant(bool kill) {
    if (kill && occupant) delete occupant;
    occupant=NULL;
    occupied = false;
    mp->notify(symbol, row, column);
}

void Cell::addNeighbour(Cell *cll) {
    neighbours[numNeighbours] = cll;
    numNeighbours++;
}

int Cell::amtNeighbours() {
    return numNeighbours;
}

Cell *Cell::getNeighbour(int x) {
    if (x < numNeighbours) return neighbours[x];
    else return NULL;
}

bool Cell::replaceNeighbour(Cell *cll) {
    for (int i=0; i<numNeighbours; i++) {
        int r = neighbours[i]->getRow();
        int c = neighbours[i]->getCol();
        if (cll->getRow()==r && cll->getCol()==c) {
            neighbours[i]=cll;
            return true;
        }
    }

    return false;
}

int Cell::getCID() {
    return chamberID;
}

void Cell::setCID(int id) {
    chamberID = id;
}

