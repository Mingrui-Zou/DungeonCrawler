#include <cstdlib>
#include <sstream>
#include <string>
#include "gameobject.h"
#include "character.h"
#include "treasure.h"
#include "player.h"
#include "map.h"
#include "cell.h"
#include "npc.h"
#include "diggle.h"
using namespace std;

Diggle::Diggle(int row, int col, Map *mp, Player *pc):
    NPC(row, col, mp, 'd', "Diggle", 60, 60, 15, 15, 1, true, pc) {}

Diggle::~Diggle() {}


void NPC::drop() {
    int r = getRow();
    int c = getCol();
    
    Treasure *gold = new Treasure(r, c, mp, dropGold);
    Cell *cll = mp->getCell(r, c);
    cll->clearOccupant(false);
    cll->setOccupant(gold);

}
