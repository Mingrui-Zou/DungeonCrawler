#ifndef __BOOSTATK_H__
#define __BOOSTATK_H__
#include <string>
#include "potion.h"

class Map;
class Human;
class Elf;
class Dwarf;
class Ork;

class BoostAtk: public Potion {

    public:
    BoostAtk(int row, int col, Map *mp);
    ~BoostAtk();

    std::string use(Human *pc);
    std::string use(Elf *pc);
    std::string use(Dwarf *pc);
    std::string use(Ork *pc);

};



#endif
