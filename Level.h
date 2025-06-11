#ifndef LEVEL_H
#define LEVEL_H

#include<iostream>
#include<vector>
#include"Dungeon.h"

using namespace std;

class Level {
    Dungeon* dungeon;
    //vector<Entity> Entities;

public:
    Level();
    ~Level();
    void LoadDungeon(ifstream& read);
    void Draw();
};

#endif // !LEVEL_H
