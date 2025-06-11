#include "Level.h"

Level::Level() : dungeon(nullptr) {}

Level::~Level() {
    delete dungeon;
}

void Level::LoadDungeon(ifstream& read) {
    if (dungeon) delete dungeon;
    dungeon = new Dungeon();
    dungeon->Set_Dungeon(read);
}

void Level::Draw() {
    if (dungeon) {
        dungeon->Draw_Dungeon();
    }
}