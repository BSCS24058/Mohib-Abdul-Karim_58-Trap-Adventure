#ifndef DUNGEON_HG
#define DUNGEON_H

#include<iostream>
#include<string>
#include<fstream>
#include"raylib.h"
#include"Globals.h"
#include<vector>
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
	float x_offset;
	float y_offset;

	vector<Vector2> Trap_Positions;
	Vector2 playerOriginalPosition;


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
	vector<Vector2> GetTrapPositions() const;
	Vector2 GetPlayerOriginalPosition() const;

	void Draw_Dungeon();

	~Dungeon();
};




#endif // !DUNGEON_HG

