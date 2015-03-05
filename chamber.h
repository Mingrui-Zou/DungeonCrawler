#ifndef __CHAMBER_H__
#define __CHAMBER_H__
#include <vector>

class GameObject;
class Player;
class NPC;
class Potion;
class Treasure;
class Cell;
class Map;

class Chamber {
    int ID, numObjects, numCells;
    std::vector<Cell*> cells;

    void swap(int a, int b);

    public:
    Chamber(int ID);
    ~Chamber();

    int getID();
    int getNumObjects();
    int getNumCells();
    void addCell(Cell *cll);

    //spawn methods coming soon, maybe just have one spawn function
    bool spawn(Player *pc);
    bool spawn(NPC *npc);
    bool spawn(Potion *potion);
    bool spawn(Treasure *gold, Map *mp, Player *pc);
    bool spawn(Cell *stair, Map *mp);
};

#endif
