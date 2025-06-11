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
	void setDungeon(Dungeon* dungeon);
    void LoadDungeon(ifstream& read);
    void DrawLevel();
};

#endif // !LEVEL_H
