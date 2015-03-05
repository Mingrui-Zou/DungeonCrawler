#include "character.h"
#include "gameobject.h"
#include "map.h"
#include "stair.h"

Stair::Stair(int row, int col, Map *mp):
    Cell(row, col, mp, '\\', "Stair", true, -1) {}

Stair::~Stair() {}

//doesn't put target in Occupant
bool Stair::setOccupant(Character *target) {
    if (target->getSym()=='@') {
        target->setRow(row);
        target->setCol(column);
        mp->nextFloor();
        return true;        //remove prev pointer of pc outside
    } else {
        return false;
    }
}
