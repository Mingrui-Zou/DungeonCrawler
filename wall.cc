#include "wall.h"
#include "cell.h"
#include "map.h"
using namespace std;

Wall::Wall(int row, int col, Map *mp, char sym): 
    Cell(row, col, mp, sym, "Wall", true, -1) {}

Wall::~Wall() {}

void Wall::clearOccupant(bool kill) {}   //wall has no occupant
