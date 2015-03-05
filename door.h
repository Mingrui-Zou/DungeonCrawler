#ifndef __DOOR_H__
#define __DOOR_H__
#include "cell.h"

class Map;
class GameObject;

class Door: public Cell {
    
    public:
        Door(int row, int col, Map* mp);
        ~Door();
        
        bool setOccupant(Character *target);
};

#endif
