#include <string>
#include "map.h"
#include "player.h"
    #include "human.h"
    #include "elf.h"
    #include "dwarf.h"
    #include "ork.h"
#include "potion.h"
#include "wounddef.h"
using namespace std;

WoundDef::WoundDef(int row, int col, Map *mp):
    Potion(row, col, mp, "Choco-Laxatives") {}

WoundDef::~WoundDef() {}

string WoundDef::use(Human *pc) {
    pc->addDef(-5);
    return name;
}

string WoundDef::use(Elf *pc) {
    name = "Protein Shake";
    pc->addDef(5);
    return name;
}

string WoundDef::use(Dwarf *pc) {
    pc->addDef(-5);
    return name;
}

string WoundDef::use(Ork *pc) {
    pc->addDef(-5);
    return name;
}
