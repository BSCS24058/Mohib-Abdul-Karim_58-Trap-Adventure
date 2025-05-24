//#include "Dungeon.h"
//
//Dungeon::Dungeon() : dungeon{ nullptr }, width{ 0 }, height{ 0 }, cell_size{0} {}
//
//void Dungeon::Set_Dungeon(ifstream& read){
//	read >> width;
//	read >> height;
//	read >> cell_size;
//
//	dungeon = new char* [width];
//	for (int i = 0; i < width; i++) {
//		dungeon[i] = new char[height];
//	}
//}
//
//int Dungeon::GetWidth() const {
//    return width;
//}
//
//int Dungeon::GetHeight() const {
//    return height;
//}
//
//int Dungeon::GetCellSize() const {
//    return cell_size;
//}
//
//char Dungeon::GetCell(int x, int y) const {
//    if (x >= 0 && x < width && y >= 0 && y < height) {
//        return dungeon[x][y]; // note: rows are height (y), columns are width (x)
//    }
//    return 'W';
//}
//
//char** Dungeon::GetMap() const {
//    return dungeon;
//}
//
//void Draw_Dungeon(Dungeon dun) {
//    for (int y = 0; y < dun.GetHeight(); y++) {
//        for (int x = 0; x < dun.GetWidth(); x++) {
//            if (dun.GetMap()[y][x] == 'W') {
//                Color color = (x == 0 || y == 0 || x == dun.GetWidth() - 1 || y == dun.GetHeight() - 1)
//                    ? Color{ 230, 210, 80, 255 }
//                : DARKGRAY;
//                DrawRectangle(x * dun.GetCellSize(), y * dun.GetCellSize(), dun.GetCellSize(), dun.GetCellSize(), color);
//            }
//            else {
//                DrawRectangle(x * dun.GetCellSize(), y * dun.GetCellSize(), dun.GetCellSize(), dun.GetCellSize(), Color{ 144, 238, 144, 255 });
//            }
//        }
//    }
//
//    DrawRectangle(playerPixelX, playerPixelY, CELL_SIZE, CELL_SIZE, RED);
//}
