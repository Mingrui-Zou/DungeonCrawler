#ifndef __POISON_H__
#define __POISON_H__
#include <string>
#include "potion.h"

class Map;
class Human;
class Elf;
class Dwarf;
class Ork;

class Poison: public Potion {
    
    public:
    Poison(int row, int col, Map *mp);
    ~Poison();

    std::string use(Human *pc);
    std::string use(Elf *pc);
    std::string use(Dwarf *pc);
    std::string use(Ork *pc);
};


#endif
