#ifndef LEVEL_H
#define LEVEL_H

#include<iostream>
#include<vector>
#include"Dungeon.h"

using namespace std;

class Level {
    Dungeon* dungeon;
    

public:
    Level();
    ~Level();
	void setDungeon(Dungeon* dungeon);
	Dungeon* getDungeon() const;
    void LoadDungeon(ifstream& read);
    void DrawLevel(Player* Pl);
};

#endif // !LEVEL_H
