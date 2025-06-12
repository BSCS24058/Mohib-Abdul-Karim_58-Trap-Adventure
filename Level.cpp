#include "Level.h"

Level::Level() : dungeon(nullptr) {}

Level::~Level() {
    delete dungeon;
}

void Level::setDungeon(Dungeon* dungeon){
    if (this->dungeon) delete this->dungeon;
	this->dungeon = dungeon;
}

Dungeon* Level::getDungeon() const{
	return dungeon;
}

void Level::LoadDungeon(ifstream& read) {
    if (dungeon) delete dungeon;
    dungeon = new Dungeon();
    dungeon->Set_Dungeon(read);
}

void Level::DrawLevel(Player* Pl) {
    if (dungeon) {
        dungeon->Draw_Dungeon(Pl);
    }
}