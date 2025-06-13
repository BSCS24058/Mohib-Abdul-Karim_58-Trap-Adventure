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
	//vector<Obstacles*> obstacles;
	int No_of_Obstacles;
    

public:
    Level();
    ~Level();
	void setDungeon(Dungeon* dungeon);
	Dungeon* getDungeon() const;
    void LoadDungeon(ifstream& read, Player* Pl);
    void DrawLevel();
	void AddObstacle();

    //vector<Obstacles*>& getObstacles();
};

#endif // !LEVEL_H
