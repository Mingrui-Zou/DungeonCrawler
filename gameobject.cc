#include <string>
#include "gameobject.h"
#include "map.h"
using namespace std;

GameObject::GameObject(int row, int column, Map *mp, char sym, string name): 
    row(row), 
    column(column), 
    mp(mp),
    symbol(sym),
    name(name) {}

GameObject::~GameObject() {
}    //doesn't delete mp, mp destructor called before GameObject destructor

bool GameObject::setDir(int &r, int &c, string dir) {
    
    //sets up directional matrix
    if (dir=="no" && row>0) r--;
    else if (dir=="so" && row<HEIGHT-1) r++;
    else if (dir=="we" && column>0) c--;
    else if (dir=="ea" && column<WIDTH-1) c++;
    else if (dir=="nw" && row>0 && column>0) {r--; c--;}
    else if (dir=="sw" && row<HEIGHT-1 && column>0) {r++; c--;}
    else if (dir=="ne" && row>0 && column<WIDTH-1) {r--; c++;}
    else if (dir=="se" && row<HEIGHT-1 && column<WIDTH-1) {r++; c++;}
    else {return false;}

    return true;

}

string GameObject::getDir(string dir) {
    if (dir=="no") return "North";
    else if (dir=="so") return "South";
    else if (dir=="we") return "West";
    else if (dir=="ea") return "East";
    else if (dir=="nw") return "North-West";
    else if (dir=="sw") return "South-West";
    else if (dir=="ne") return "North-East";
    else if (dir=="se") return "South-East";
    else return "Invalid Dir given to getDir in GameObject";

}

int GameObject::getRow() {
    return row;
}

int GameObject::getCol() {
    return column;
}

void GameObject::setRow(int r) {
    row=r;
}

void GameObject::setCol(int c) {
    column=c;
}

char GameObject::getSym() {
    return symbol;
}

string GameObject::getName() {
    return name;
}

void GameObject::notifyMap() {
    mp->notify(symbol, row, column);
}
