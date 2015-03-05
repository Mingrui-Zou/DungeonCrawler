#include "door.h"
#include "gameobject.h"
#include "character.h"
#include "cell.h"
#include "map.h"
using namespace std;

Door::Door(int row, int col, Map *mp):
    Cell(row, col, mp, '+', "Door", false, -1) {}

Door::~Door() {}

bool Door::setOccupant(Character *target) {
    if (target->getSym()=='@' && !occupied) {
        occupant = target;
        target->setRow(row);
        target->setCol(column);
        occupied = true;
        mp->notify('@', row, column);
        return true;
    } else {
        return false;
    }
}
