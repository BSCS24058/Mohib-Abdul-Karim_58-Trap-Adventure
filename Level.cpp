#include "Level.h"
#include "Dungeon.h"


Level::Level() : dungeon(nullptr) {}


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
}

void Level::DrawLevel() {
    if (dungeon) {
        dungeon->Draw_Dungeon();
    }
}

//void Level::AddObstacle(){
//    Obstacles* obstacle = new Trap();
//	obstacles.push_back(obstacle);
//}

//vector<Obstacles*>& Level::getObstacles() {
//    return obstacles;
//}


Level::~Level() {
    delete dungeon;
}