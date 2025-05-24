//#include "raylib.h"
//#include <cmath>
//
//const int CELL_SIZE = 40;
//const int MAZE_WIDTH = 10;
//const int MAZE_HEIGHT = 10;
//
//char maze[MAZE_HEIGHT][MAZE_WIDTH] = {
//    {'W','W','W','W','W','W','W','W','W','W'},
//    {'W',' ',' ',' ','W',' ',' ',' ',' ','W'},
//    {'W','W','W',' ','W',' ','W','W',' ','W'},
//    {'W',' ','W',' ',' ',' ','W',' ',' ','W'},
//    {'W',' ','W','W','W',' ','W','W','W','W'},
//    {'W',' ',' ',' ',' ',' ',' ',' ',' ','W'},
//    {'W','W','W','W','W','W','W','W',' ','W'},
//    {'W',' ',' ',' ',' ',' ',' ','W',' ','W'},
//    {'W',' ','W','W','W','W',' ','W',' ','W'},
//    {'W','W','W','W','W','W','W','W','W','W'},
//};
//
//int playerX = 1; // starting position
//int playerY = 1;
//
//float playerPixelX = 1 * CELL_SIZE;
//float playerPixelY = 1 * CELL_SIZE;
//
//int targetX = 1;
//int targetY = 1;
//
//const float PLAYER_SPEED = 10000f; // pixels per frame
//
//
//void HandleInput() {
//    if (playerPixelX == targetX * CELL_SIZE && playerPixelY == targetY * CELL_SIZE) {
//        if (IsKeyPressed(KEY_RIGHT) && maze[targetY][targetX + 1] != 'W') targetX++;
//        if (IsKeyPressed(KEY_LEFT) && maze[targetY][targetX - 1] != 'W') targetX--;
//        if (IsKeyPressed(KEY_UP) && maze[targetY - 1][targetX] != 'W') targetY--;
//        if (IsKeyPressed(KEY_DOWN) && maze[targetY + 1][targetX] != 'W') targetY++;
//    }
//}
//
//void DrawMaze() {
//    for (int y = 0; y < MAZE_HEIGHT; y++) {
//        for (int x = 0; x < MAZE_WIDTH; x++) {
//            if (maze[y][x] == 'W') {
//                Color color = (x == 0 || y == 0 || x == MAZE_WIDTH - 1 || y == MAZE_HEIGHT - 1)
//                    ? Color{ 230, 210, 80, 255 }
//                : DARKGRAY;
//                DrawRectangle(x * CELL_SIZE, y * CELL_SIZE, CELL_SIZE, CELL_SIZE, color);
//            }
//            else {
//                DrawRectangle(x * CELL_SIZE, y * CELL_SIZE, CELL_SIZE, CELL_SIZE, Color{ 144, 238, 144, 255 });
//            }
//        }
//    }
//
//    DrawRectangle(playerPixelX, playerPixelY, CELL_SIZE, CELL_SIZE, RED);
//}
//
//
//void UpdatePlayerPosition() {
//    float targetPixelX = targetX * CELL_SIZE;
//    float targetPixelY = targetY * CELL_SIZE;
//
//    if (playerPixelX < targetPixelX)
//        playerPixelX = fmin(playerPixelX + PLAYER_SPEED, targetPixelX);
//    if (playerPixelX > targetPixelX)
//        playerPixelX = fmax(playerPixelX - PLAYER_SPEED, targetPixelX);
//
//    if (playerPixelY < targetPixelY)
//        playerPixelY = fmin(playerPixelY + PLAYER_SPEED, targetPixelY);
//    if (playerPixelY > targetPixelY)
//        playerPixelY = fmax(playerPixelY - PLAYER_SPEED, targetPixelY);
//}
//
//
//int main() {
//    InitWindow(MAZE_WIDTH * CELL_SIZE, MAZE_HEIGHT * CELL_SIZE, "Trap Adventure - Simple Maze");
//    SetTargetFPS(60);
//
//    while (!WindowShouldClose()) {
//        HandleInput();           // Check for new input
//        UpdatePlayerPosition();  // Animate player toward target
//
//        BeginDrawing();
//        ClearBackground(BLACK);
//        DrawMaze();
//        EndDrawing();
//    }
//
//
//    CloseWindow();
//    return 0;
//}




// ==================Button===========================


//#include <raylib.h>
//#include <iostream>
//#include "button.hpp"
//
//int main()
//{
//    InitWindow(800, 600, "Raylib Buttons Tutorial");
//
//    SetTargetFPS(60);
//
//    Texture2D background = LoadTexture("C:/Users/User/OneDrive/Documents/Project1/background.png");
//    Button startButton{ "C:/Users/User/OneDrive/Documents/Project1/End_Button.png", {10, 10}, 0.1 };
//    Button exitButton{ "C:/Users/User/OneDrive/Documents/Project1/Start_Button (3).png", {10, 50}, 0.1 };
//    bool exit = false;
//
//    while (WindowShouldClose() == false && exit == false)
//    {
//        Vector2 mousePosition = GetMousePosition();
//        bool mousePressed = IsMouseButtonPressed(MOUSE_BUTTON_LEFT);
//
//        if (startButton.isPressed(mousePosition, mousePressed))
//        {
//            std::cout << "Start Button Pressed" << std::endl;
//        }
//
//        if (exitButton.isPressed(mousePosition, mousePressed))
//        {
//            exit = true;
//        }
//
//        BeginDrawing();
//        ClearBackground(BLACK);
//        DrawTexture(background, 0, 0, WHITE);
//        startButton.Draw();
//        exitButton.Draw();
//        EndDrawing();
//    }
//    CloseWindow();
//}