#include <ctime>
#include <cstdlib>
#include "cell.h"
#include "chamber.h"

template <class Object>
bool Chamber::spawn(Object *obj) {
    srand(time(NULL));
    int pos = rand()%(numCells-numObjects)+numObjects;

    Cell *tmp = cells[pos];
    cells[pos] = cells[numObjects];
    cells[numObjects] = tmp;

    if (cells[numObjects]->setOccupant(obj)) {
        numObjects++;
        return true;
    } else {
        return false;
    }
}
