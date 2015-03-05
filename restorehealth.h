#ifndef __RESTOREHEALTH_H__
#define __RESTOREHEALTH_H__
#include <string>
#include "potion.h"

class Map;
class Human;
class Elf;
class Dwarf;
class Ork;

class RestoreHealth: public Potion {
    
    public:
    RestoreHealth(int row, int col, Map *mp);
    ~RestoreHealth();

    std::string use(Human *pc);
    std::string use(Elf *pc);
    std::string use(Dwarf *pc);
    std::string use(Ork *pc);
};



#endif
