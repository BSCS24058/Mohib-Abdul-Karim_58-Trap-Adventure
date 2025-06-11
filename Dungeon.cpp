#include "Dungeon.h"


Dungeon::Dungeon() : dungeon{ nullptr }, width{ 0 }, height{ 0 }, cell_size{0} {}

void Dungeon::Set_Dungeon(ifstream& read) {
    read >> width >> height;

    int wr, wg, wb, wa;
    int pr, pg, pb, pa;
    read >> wr >> wg >> wb >> wa;
    read >> pr >> pg >> pb >> pa;

    Wall_Colour = Color{ (unsigned char)wr, (unsigned char)wg, (unsigned char)wb, (unsigned char)wa };
    Path_Colour = Color{ (unsigned char)pr, (unsigned char)pg, (unsigned char)pb, (unsigned char)pa };

    // Fit dungeon to screen
    cell_size = std::min(screenWidth / width, screenHeight / height);

    read.ignore(); // ignore newline after color values

    // Allocate row-major 2D array: dungeon[y][x]
    dungeon = new char* [height];
    for (int y = 0; y < height; y++) {
        dungeon[y] = new char[width];
    }

    // Read map row-by-row
    for (int y = 0; y < height; y++) {
        string line;
        getline(read, line);
        for (int x = 0; x < width; x++) {
            dungeon[y][x] = (x < (int)line.length()) ? line[x] : 'W';
        }
    }
}



int Dungeon::GetWidth() const {
    return width;
}

int Dungeon::GetHeight() const {
    return height;
}

int Dungeon::GetCellSize() const {
    return cell_size;
}

char Dungeon::GetCell(int x, int y) const {
    if (x >= 0 && x < width && y >= 0 && y < height) {
        return dungeon[y][x]; // row-major
    }
    return 'W';
}


char** Dungeon::GetMap() const {
    return dungeon;
}

void Dungeon::Draw_Dungeon() {
    int x_offset = (screenWidth - width * cell_size) / 2;
    int y_offset = (screenHeight - height * cell_size) / 2;

    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            int draw_x = x * cell_size + x_offset;
            int draw_y = y * cell_size + y_offset;

            if (dungeon[y][x] == 'W') {
                Color color = ((x == 0 || y == 0 || x == width - 1 || y == height - 1)
                    ? Wall_Colour
                    : DARKGRAY);
                DrawRectangle(draw_x, draw_y, cell_size, cell_size, color);
            }
            else {
                DrawRectangle(draw_x, draw_y, cell_size, cell_size, Path_Colour);
            }
        }
    }
}


