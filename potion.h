#ifndef __POTION_H__
#define __POTION_H__
#include <string>
#include "character.h"

class Map;
class Human;
class Elf;
class Dwarf;
class Ork;
//class Druid;

class Potion: public Character {
    
    public:
    Potion(int row, int col, Map *mp, std::string name);
    virtual ~Potion();
    
    virtual bool isPotion();

    virtual std::string use(Human *pc)=0;
    virtual std::string use(Elf *pc)=0;
    virtual std::string use(Dwarf *pc)=0;
    virtual std::string use(Ork *pc)=0;
    //virtual std::string use(Druid *pc)=0;
};

#endif
