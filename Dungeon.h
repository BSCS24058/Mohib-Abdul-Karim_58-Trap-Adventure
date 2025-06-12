#ifndef DUNGEON_HG
#define DUNGEON_H

#include<iostream>
#include<string>
#include<fstream>
#include"raylib.h"
#include"Player.h"
#include"Globals.h"
using namespace std;

class Dungeon {
	char** dungeon;
	int width;
	int height;
	float cell_size;
	Color Wall_Colour;
	Color Path_Colour;
	int offsetX = 0;
	int offsetY = 0;

	Texture2D wallTexture;

public:
	Dungeon();
	void Set_Dungeon(ifstream& read);
	int GetWidth() const;
	int GetHeight() const;
	float GetCellSize() const;
	char GetCell(int x, int y) const;
	char** GetMap() const;

	void Draw_Dungeon(Player* Pl);

	~Dungeon();
};




#endif // !DUNGEON_HG

