#include "Dungeon.h"
#include "Player.h"


Dungeon::Dungeon() : dungeon{ nullptr }, width{ 0 }, height{ 0 }, cell_size{ 0 } {
    wallTexture = LoadTexture("C:/Github Repositories/Trap-Adventure-Game/wall.jpg");
}

void Dungeon::Set_Dungeon(ifstream& read, Player* Pl, Level* lvl) {
    read >> width >> height;

    int wr, wg, wb, wa;
    int pr, pg, pb, pa;
    read >> wr >> wg >> wb >> wa;
    read >> pr >> pg >> pb >> pa;

    Wall_Colour = Color{ (unsigned char)wr, (unsigned char)wg, (unsigned char)wb, (unsigned char)wa };
    Path_Colour = Color{ (unsigned char)pr, (unsigned char)pg, (unsigned char)pb, (unsigned char)pa };

    cell_size = std::min(screenWidth / width, screenHeight / height);

    read.ignore(); 

    dungeon = new char* [height];
    for (int y = 0; y < height; y++) {
        dungeon[y] = new char[width];
    }

    for (int y = 0; y < height; y++) {
        string line;
        getline(read, line);
        for (int x = 0; x < width; x++) {
            dungeon[y][x] = (x < (int)line.length()) ? line[x] : 'W';
        }
    }

    x_offset = (screenWidth - width * cell_size) / 2;
    y_offset = (screenHeight - height * cell_size) / 2;

    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            if (dungeon[y][x] == 'X') {
				playerOriginalPosition = { x * cell_size + x_offset, y * cell_size + y_offset };
                Pl->SetPosition(x * cell_size + x_offset, y * cell_size + y_offset);
            }
            if (dungeon[y][x] == 'T') {

                Trap_Positions.push_back({ x * cell_size + x_offset, y * cell_size + y_offset });
            }
        }
    }
}



int Dungeon::GetWidth() const {
    return width;
}

int Dungeon::GetHeight() const {
    return height;
}

float Dungeon::GetCellSize() const {
    return cell_size;
}

char Dungeon::GetCell(int x, int y) const {
    if (y >= 0 && y < height && x >= 0 && x < width)
        return dungeon[y][x];  
    return 'W';  
}


char** Dungeon::GetMap() const {
    return dungeon;
}

int Dungeon::GetXOffset() const {
    return x_offset;
}

int Dungeon::GetYOffset() const {
    return y_offset;
}

void Dungeon::Draw_Dungeon() {


    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            int draw_x = x * cell_size + x_offset;
            int draw_y = y * cell_size + y_offset;

            if (dungeon[y][x] == 'W') {
                DrawTextureEx(wallTexture,Vector2{ static_cast<float>(draw_x), static_cast<float>(draw_y) },
                    0.0f,
                    static_cast<float>(cell_size) / wallTexture.width,
                    WHITE);
            }
            else {
                DrawRectangle(draw_x, draw_y, cell_size, cell_size, Path_Colour);
            }
        }
    }

}

vector<Vector2> Dungeon::GetTrapPositions() const {
    return Trap_Positions;
}

Vector2 Dungeon::GetPlayerOriginalPosition() const{
    return playerOriginalPosition;
}


Dungeon::~Dungeon() {
    for (int i = 0; i < height; i++) {
        delete[] dungeon[i];
    }
    delete[] dungeon;
    dungeon = nullptr;
    width = 0;
    height = 0;
    cell_size = 0;
    UnloadTexture(wallTexture);
}