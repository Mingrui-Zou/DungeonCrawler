#ifndef __DIGGLEEGG_H__
#define __DIGGLEEGG_H__
#include <string>
#include "potion.h"

class Map;
class Human;
class Elf;
class Dwarf;
class Ork;

class DiggleEgg: public Potion {
    
    public:
    DiggleEgg(int row, int col, Map *mp);
    ~DiggleEgg();

    std::string use(Human *pc);
    std::string use(Elf *pc);
    std::string use(Dwarf *pc);
    std::string use(Ork *pc);
};




#endif
