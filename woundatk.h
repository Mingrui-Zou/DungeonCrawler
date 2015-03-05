#ifndef __WOUNDATK_H__
#define __WOUNDATK_H__
#include <string>
#include "potion.h"

class Map;
class Human;
class Elf;
class Dwarf;
class Ork;

class WoundAtk: public Potion {

    public:
    WoundAtk(int row, int col, Map *mp);
    ~WoundAtk();

    std::string use(Human *pc);
    std::string use(Elf *pc);
    std::string use(Dwarf *pc);
    std::string use(Ork *pc);

};



#endif
