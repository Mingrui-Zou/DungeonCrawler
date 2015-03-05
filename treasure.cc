#include <string>
#include "map.h"
#include "treasure.h"
#include "character.h"

Treasure::Treasure(int row, int col, Map *mp, int value): 
    Character(row, col, mp, '$', "Gold", 1000000, 1000000, 0, 1000000), 
    value(value) {}

Treasure::~Treasure() {}

void Treasure::killDragon() {}

bool Treasure::isTreasure() {
    return true;
}

int Treasure::getVal() {
    return value;
}

