#ifndef LEVEL_H
#define LEVEL_H

#include<iostream>
#include<vector>
#include"Obstacles.h"
#include"Trap.h"

class Player;
class Dungeon;

using namespace std;

class Level {
    Dungeon* dungeon;
	vector<Obstacles*> obstacles;
	int No_of_Obstacles;
    

public:
    Level();
	void setDungeon(Dungeon* dungeon);
	Dungeon* getDungeon() const;
    void LoadDungeon(ifstream& read, Player* Pl);
    void DrawLevel();
	vector<Obstacles*> getObstacles();
	int getNo_of_Obstacles();

    ~Level();
};

#endif // !LEVEL_H
