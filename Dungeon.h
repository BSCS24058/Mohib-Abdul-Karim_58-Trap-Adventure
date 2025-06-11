#ifndef DUNGEON_HG
#define DUNGEON_H

#include<iostream>
#include<fstream>
#include"raylib.h"
using namespace std;

class Dungeon {
	char** dungeon;
	int width;
	int height;
	int cell_size;
	Color Wall_Colour;
	Color Path_Colour;

public:
	Dungeon();
	void Set_Dungeon(ifstream& read);
	int GetWidth() const;
	int GetHeight() const;
	int GetCellSize() const;
	char GetCell(int x, int y) const;
	char** GetMap() const;

	void Draw_Dungeon();
};




#endif // !DUNGEON_HG

