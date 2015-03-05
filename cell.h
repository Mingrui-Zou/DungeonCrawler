#ifndef __CELL_H__
#define __CELL_H__
#include <string>
#include "gameobject.h"

const int MAXNEIGHBOURS = 8;

class Map;
class Character;

class Cell: public GameObject {
    protected:
        bool occupied;
        Character *occupant;
        int numNeighbours;
        Cell *neighbours[MAXNEIGHBOURS];
        int chamberID;
        
        Cell(int r, int c, Map *mp, char sym, std::string name, bool occ, int CID);

    public:
        virtual ~Cell();
        
        bool isOccupied();
        Character *getOccupant();
        virtual bool setOccupant(Character *target);
        virtual void clearOccupant(bool kill);
        
        void addNeighbour(Cell* cll);
        int amtNeighbours();
        Cell *getNeighbour(int x);
        bool replaceNeighbour(Cell *cll);

        int getCID();
        void setCID(int id);
};

#endif
