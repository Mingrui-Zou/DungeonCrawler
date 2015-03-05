#include <string>
#include "map.h"
#include "player.h"
    #include "human.h"
    #include "elf.h"
    #include "dwarf.h"
    #include "ork.h"
#include "potion.h"
#include "boostatk.h"
using namespace std;

BoostAtk::BoostAtk(int row, int col, Map *mp):
    Potion(row, col, mp, "Vodka") {}

BoostAtk::~BoostAtk() {}

string BoostAtk::use(Human *pc) {
    pc->addAtk(5);
    return name;
}

string BoostAtk::use(Elf *pc) {
    pc->addAtk(5);
    return name;
}

string BoostAtk::use(Dwarf *pc) {
    pc->addAtk(5);
    return name;
}

string BoostAtk::use(Ork *pc) {
    pc->addAtk(5);
    return name;
}
