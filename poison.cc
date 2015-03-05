#include <string>
#include "map.h"
#include "player.h"
    #include "human.h"
    #include "elf.h"
    #include "dwarf.h"
    #include "ork.h"
#include "potion.h"
#include "poison.h"
using namespace std;

Poison::Poison(int row, int col, Map *mp):
    Potion(row, col, mp, "Poison") {}

Poison::~Poison() {}

string Poison::use(Human *pc) {
    pc->resHealth(-5);
    return name;
}

string Poison::use(Elf *pc) {
    name = "Potion";
    pc->resHealth(5);
    return name;
}

string Poison::use(Dwarf *pc) {
    pc->resHealth(-5);
    return name;
}

string Poison::use(Ork *pc) {
    pc->resHealth(-5);
    return name;
}
