#ifndef DUNGEON_HG
#define DUNGEON_H

#include<iostream>
#include<string>
#include<fstream>
#include"raylib.h"
#include"Globals.h"
using namespace std;

class Player;
class Level;

class Dungeon {
	char** dungeon;
	int width;
	int height;
	float cell_size;
	Color Wall_Colour;
	Color Path_Colour;
	int x_offset;
	int y_offset;

	Texture2D wallTexture;

public:
	Dungeon();
	void Set_Dungeon(ifstream& read, Player* Pl, Level* lvl);
	int GetWidth() const;
	int GetHeight() const;
	float GetCellSize() const;
	char GetCell(int x, int y) const;
	char** GetMap() const;

	int GetXOffset() const;
	int GetYOffset() const;

	void Draw_Dungeon();

	~Dungeon();
};




#endif // !DUNGEON_HG

