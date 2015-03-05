#ifndef __GAMEOBJECT_H__
#define __GAMEOBJECT_H__
#include <string>

class Map;

class GameObject {
    protected:
        int row, column;
        Map *mp;
        char symbol;        //symbol could change to denote status
        std::string name;        //string could change

        GameObject(int row, int column, Map *mp, char sym, std::string name);

        bool setDir(int &r, int &c, std::string dir);
        std::string getDir(std::string dir);

    public:
        virtual ~GameObject();
        
        int getRow();
        int getCol();
        void setRow(int r);
        void setCol(int c);
        char getSym();
        std::string getName();
        void notifyMap();
};

#endif
