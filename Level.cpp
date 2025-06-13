#include "Level.h"
#include "Dungeon.h"
#include"Trap.h"


Level::Level() : dungeon(nullptr), No_of_Obstacles{0} {}


void Level::setDungeon(Dungeon* dungeon){
    if (this->dungeon) delete this->dungeon;
	this->dungeon = dungeon;
}

Dungeon* Level::getDungeon() const{
	return dungeon;
}

void Level::LoadDungeon(ifstream& read, Player* Pl) {
    if (dungeon) delete dungeon;
    dungeon = new Dungeon();
    dungeon->Set_Dungeon(read, Pl, this);

    vector<Vector2> trapPositions = dungeon->GetTrapPositions();

    float csize = dungeon->GetCellSize();
    for (Vector2 pos : trapPositions) {
        obstacles.push_back(new Trap(pos.x, pos.y));
    }

    No_of_Obstacles = obstacles.size();


}

void Level::DrawLevel() {
    if (dungeon) {
        dungeon->Draw_Dungeon();
    }
}

vector<Obstacles*> Level::getObstacles(){
    return obstacles;
}

int Level::getNo_of_Obstacles() {
	return No_of_Obstacles;
}



Level::~Level() {
    delete dungeon;
    for (Obstacles* obs : obstacles) {
        delete obs;
    }
}