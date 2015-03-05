#include <string>
#include "potion.h"
using namespace std;

Potion::Potion(int row, int col, Map *mp, string name):
    Character(row, col, mp, 'P', name, 1000000, 1000000, 0, 1000000) {}

Potion::~Potion() {}

bool Potion::isPotion() {
    return true;
}
