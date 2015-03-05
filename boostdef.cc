#include <string>
#include "map.h"
#include "player.h"
    #include "human.h"
    #include "elf.h"
    #include "dwarf.h"
    #include "ork.h"
#include "potion.h"
#include "boostdef.h"
using namespace std;

BoostDef::BoostDef(int row, int col, Map *mp):
    Potion(row, col, mp, "Protein Shake") {}

BoostDef::~BoostDef() {}

string BoostDef::use(Human *pc) {
    pc->addDef(5);
    return name;
}

string BoostDef::use(Elf *pc) {
    pc->addDef(5);
    return name;
}

string BoostDef::use(Dwarf *pc) {
    pc->addDef(5);
    return name;
}

string BoostDef::use(Ork *pc) {
    pc->addDef(5);
    return name;
}
