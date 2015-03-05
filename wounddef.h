#ifndef __WOUNDDEF_H__
#define __WOUNDDEF_H__
#include <string>
#include "potion.h"

class Map;
class Human;
class Elf;
class Dwarf;
class Ork;

class WoundDef: public Potion {

    public:
    WoundDef(int row, int col, Map *mp);
    ~WoundDef();

    std::string use(Human *pc);
    std::string use(Elf *pc);
    std::string use(Dwarf *pc);
    std::string use(Ork *pc);

};



#endif
