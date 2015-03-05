#include <sstream>
#include <cstdlib>
#include <string>
#include "map.h"
#include "player.h"
    #include "human.h"
    #include "elf.h"
    #include "dwarf.h"
    #include "ork.h"
#include "potion.h"
    #include "diggleegg.h"
using namespace std;

DiggleEgg::DiggleEgg(int row, int col, Map *mp):
Potion(row, col, mp, "Diggle Egg") {}

DiggleEgg::~DiggleEgg() {}

string DiggleEgg::use(Human *pc) {
    if (rand()%3>=1) {
        pc->resHealth(10);
    } else {
        pc->resHealth(-15);
        ss << pc->name << " gets Salmonella.";
        mp->addInfo(ss.str());
    }
    
    return name;
}

string DiggleEgg::use(Elf *pc) {
pc->resHealth(5);
return name;
}

string DiggleEgg::use(Dwarf *pc) {
    if (rand()%3>=1) {
        pc->resHealth(10);
    } else {
        pc->resHealth(-15);
        ss << pc->name << " gets Salmonella.";
        mp->addInfo(ss.str());
    }
    
    return name;
}

string DiggleEgg::use(Ork *pc) {
pc->resHealth(5);
return name;
}

