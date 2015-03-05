#include "passage.h"
#include "cell.h"
#include "map.h"
using namespace std;

Passage::Passage(int row, int col, Map *mp):
    Cell(row, col, mp, '#', "Passage", false, -1) {}

Passage::~Passage() {}
