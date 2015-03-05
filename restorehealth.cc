#include <string>
#include "map.h"
#include "player.h"
    #include "human.h"
    #include "elf.h"
    #include "dwarf.h"
    #include "ork.h"
#include "potion.h"
#include "restorehealth.h"
using namespace std;

RestoreHealth::RestoreHealth(int row, int col, Map *mp):
    Potion(row, col, mp, "Potion") {}

RestoreHealth::~RestoreHealth() {}

string RestoreHealth::use(Human *pc) {
    pc->resHealth(5);
    return name;
}

string RestoreHealth::use(Elf *pc) {
    pc->resHealth(5);
    return name;
}

string RestoreHealth::use(Dwarf *pc) {
    pc->resHealth(5);
    return name;
}

string RestoreHealth::use(Ork *pc) {
    pc->resHealth(5);
    return name;
}
