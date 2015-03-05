#ifndef __BOOSTDEF_H__
#define __BOOSTDEF_H__
#include <string>
#include "potion.h"

class Map;
class Human;
class Elf;
class Dwarf;
class Ork;

class BoostDef: public Potion {

    public:
    BoostDef(int row, int col, Map *mp);
    ~BoostDef();

    std::string use(Human *pc);
    std::string use(Elf *pc);
    std::string use(Dwarf *pc);
    std::string use(Ork *pc);

};



#endif
