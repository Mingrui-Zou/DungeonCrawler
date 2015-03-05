#include "floor.h"
#include "cell.h"
#include "map.h"
using namespace std;

Floor::Floor(int row, int col, Map *mp): 
    Cell(row, col, mp, '.', "Floor", false, 0) {}

Floor::~Floor() {}



