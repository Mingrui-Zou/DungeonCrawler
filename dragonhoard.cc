#include "treasure.h"
#include "dragonhoard.h"

DragonHoard::DragonHoard(int row, int col, Map *mp):
    Treasure(row, col, mp, DRAGONHOARDVALUE),
    dragonAlive(true) {}

DragonHoard::~DragonHoard() {}

void DragonHoard::killDragon() {
    dragonAlive = false;
}

bool DragonHoard::isTreasure() {
    return (!dragonAlive);
}
