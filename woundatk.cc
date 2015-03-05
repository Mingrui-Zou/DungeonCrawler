#include <string>
#include "map.h"
#include "player.h"
    #include "human.h"
    #include "elf.h"
    #include "dwarf.h"
    #include "ork.h"
#include "potion.h"
#include "woundatk.h"
using namespace std;

WoundAtk::WoundAtk(int row, int col, Map *mp):
    Potion(row, col, mp, "Snake Oil") {}

WoundAtk::~WoundAtk() {}

string WoundAtk::use(Human *pc) {
    pc->addAtk(-5);
    return name;
}

string WoundAtk::use(Elf *pc) {
    name = "Vodka";
    pc->addAtk(5);
    return name;
}

string WoundAtk::use(Dwarf *pc) {
    pc->addAtk(-5);
    return name;
}

string WoundAtk::use(Ork *pc) {
    pc->addAtk(-5);
    return name;
}
