#include<iostream>
#include"raylib.h"
#include<vector>
#include<iomanip>
#include<sstream>
#include"MyStr.h"
#include"button.hpp"

#define TOTAL_TITLE_FRAMES 200
#define TOTAL_MENU_FRAMES 317
#define FRAME_RATE 60

using namespace std;

MyStr GetTitlePath(int index) {
    MyStrStream ss;
    ss << "C:/Users/User/OneDrive/Documents/Project1/HomepageFrames/frames";

    int digits = 5;
    int temp = index;
    int digitCount = 0;

    if (index == 0) {
        digitCount = 1;
    }
    else {
        while (temp != 0) {
            temp /= 10;
            digitCount++;
        }
    }

    for (int i = 0; i < digits - digitCount; i++) {
        ss << '0';
    }

    ss << index;
    ss << ".png";

    return ss.str();
}
MyStr GetMenuPath(int index) {
    MyStrStream ss;
    ss << "C:/Users/User/OneDrive/Documents/Project1/MenuFrames/frame";

    int digits = 5;
    int temp = index;
    int digitCount = 0;

    if (index == 0) {
        digitCount = 1;
    }
    else {
        while (temp != 0) {
            temp /= 10;
            digitCount++;
        }
    }

    for (int i = 0; i < digits - digitCount; i++) {
        ss << '0';
    }

    ss << index;
    ss << ".png";

    return ss.str();
}

enum GameStates {
    Title,
    Title_To_Menu,
    Menu,
    Menu_To_PreStart,
    PreStart
};


int main() {
    const int screenWidth = 1280;
    const int screenHeight = 720;

    InitWindow(screenWidth, screenHeight, "Trap Adventure");
    SetTargetFPS(FRAME_RATE);

    vector<Texture2D> frames;
    for (int i = 0; i < TOTAL_TITLE_FRAMES; i++) {
        MyStr path = GetTitlePath(i);
        Image img = LoadImage(path.fetchstr());
        frames.push_back(LoadTextureFromImage(img));
        UnloadImage(img);
    }
    
    vector<Texture2D> menuFrames;
    for (int i = 0; i < TOTAL_MENU_FRAMES; i++) {
        MyStr path = GetMenuPath(i);
        Image img = LoadImage(path.fetchstr());
        menuFrames.push_back(LoadTextureFromImage(img));
        UnloadImage(img);
    }
    
    InitAudioDevice();
    Music bgMusic = LoadMusicStream("C:/Users/User/Downloads/Music/Little Nightmares 2 OST Track 1 - Little Nightmares II Main Theme_2.mp3");   // For background music
    PlayMusicStream(bgMusic);
    bgMusic.looping = true;

    GameStates Current_State = Title;

    //For Title Screen
    int framecount = 0;
    int currentFrame = 0;
    float frameTimer = 0.0f;
    int Press_Enter_Opacity = 0;
    float fade_opacity = 0.0;

    //For Menu Screen;
    float menuFadeOpacity = 0.0f;
    int menuCurrentFrame = 0;
    float menuFrameTimer = 0.0f;

    float buttonScale = 0.3f;
    Texture2D tempTex = LoadTexture("C:/Users/User/OneDrive/Documents/Project1/End_Button.png");
    int buttonWidth = tempTex.width * buttonScale;
    int buttonHeight = tempTex.height * buttonScale;
    UnloadTexture(tempTex);

    Vector2 startPos = { (float)(screenWidth - buttonWidth) / 2, (float)(screenHeight / 2 - 325) };
    Vector2 exitPos = { (float)(screenWidth - buttonWidth) / 2, (float)(screenHeight / 2-100) };

       
    Button startButton{ "C:/Users/User/OneDrive/Documents/Project1/Start_Button (3).png", startPos, buttonScale };
    Button exitButton{ "C:/Users/User/OneDrive/Documents/Project1/End_Button.png", exitPos, buttonScale };


    bool exit = false;
    while (!WindowShouldClose() && exit==false) {

        UpdateMusicStream(bgMusic);

        framecount++;


        frameTimer += GetFrameTime();
        if (frameTimer >= 1.0f / FRAME_RATE) {
            frameTimer = 0.0f;
            currentFrame = (currentFrame + 1) % TOTAL_TITLE_FRAMES;
        }

        menuFrameTimer += GetFrameTime();
        if (menuFrameTimer >= 1.0f / FRAME_RATE) {
            menuFrameTimer = 0.0f;
            menuCurrentFrame = (menuCurrentFrame + 1) % TOTAL_MENU_FRAMES;
        }


        BeginDrawing();
        ClearBackground(BLACK);

        switch (Current_State) {
        case Title:
            DrawTexture(frames[currentFrame], 0, 0, WHITE);
            if ((framecount / 60) % 2 == 0) {
                MyStr GameTitle = "Trap Adventure";
                Color Title_Colour = { 149, 6, 6, 255 };
                DrawText("Trap Adventure", ((GetScreenWidth() - MeasureText("Trap Adventure", 90)) / 2) + 1, ((GetScreenHeight() - 20) / 2) - 200,
                    90, Title_Colour);
                DrawText("Trap Adventure", ((GetScreenWidth() - MeasureText("Trap Adventure", 90)) / 2) - 1, ((GetScreenHeight() - 20) / 2) - 200,
                    90, Title_Colour);
                DrawText("Trap Adventure", (GetScreenWidth() - MeasureText("Trap Adventure", 90)) / 2, (((GetScreenHeight() - 20) / 2) + 1) - 200,
                    90, Title_Colour);
                DrawText("Trap Adventure", (GetScreenWidth() - MeasureText("Trap Adventure", 90)) / 2, (((GetScreenHeight() - 20) / 2) - 1) - 200,
                    90, Title_Colour);


                DrawText("Trap Adventure", (GetScreenWidth() - MeasureText("Trap Adventure", 90)) / 2, ((GetScreenHeight() - 20) / 2) - 200,
                    90, Title_Colour);
            }

            if (framecount > 300) {
                if (Press_Enter_Opacity < 255)
                    Press_Enter_Opacity++;
                Color PressEnter = { 149,6,6, Press_Enter_Opacity };
                const char* message = "Press Enter To Continue";
                int fontSize = 50;
                int textX = (GetScreenWidth() - MeasureText(message, fontSize)) / 2;
                int textY = ((GetScreenHeight() - 20) / 2) - 50;

                DrawText(message, textX + 1, textY, fontSize, PressEnter);
                DrawText(message, textX - 1, textY, fontSize, PressEnter);
                DrawText(message, textX, textY + 1, fontSize, PressEnter);
                DrawText(message, textX, textY - 1, fontSize, PressEnter);
                DrawText(message, textX, textY, fontSize, PressEnter);
            }
            if (IsKeyPressed(KEY_ENTER)) {
                Current_State = Title_To_Menu;
                fade_opacity = 0.0f;
            }

            break;

        case Title_To_Menu:
            DrawTexture(frames[currentFrame], 0, 0, WHITE);

            fade_opacity += GetFrameTime()/2;
            if (fade_opacity >= 1.0) {
                fade_opacity = 1.0;
                Current_State = Menu;
            }

            DrawRectangle(0, 0, screenWidth, screenHeight, Fade(BLACK, fade_opacity));
            break;


        case Menu:
            ClearBackground(BLACK);
            fade_opacity -= GetFrameTime()/2;
            if (fade_opacity <= 0.0) {
                fade_opacity = 0.0;
            }

            DrawTexture(menuFrames[menuCurrentFrame],0,0,WHITE);
            startButton.Draw();
            exitButton.Draw();
            DrawRectangle(0, 0, screenWidth, screenHeight, Fade(BLACK, fade_opacity));

            Vector2 mousePosition = GetMousePosition();
            bool mousePressed = IsMouseButtonPressed(MOUSE_BUTTON_LEFT);
            
            if (startButton.isPressed(mousePosition, mousePressed))
            {
                Current_State = Menu_To_PreStart;
            }
            
            if (exitButton.isPressed(mousePosition, mousePressed))
            {
                exit = true;
            }
            break;


       /* case Menu_To_PreStart:
            DrawTexture(menuFrames[menuCurrentFrame], 0, 0, WHITE);
            fade_opacity += GetFrameTime() / 2;
            if (fade_opacity >= 1.0) {
                fade_opacity = 1.0;
                Current_State = PreStart;
            }

            DrawRectangle(0, 0, screenWidth, screenHeight, Fade(BLACK, fade_opacity));
            break;



        case PreStart:
            ClearBackground(BLACK);
            fade_opacity -= GetFrameTime() / 2;
            if (fade_opacity <= 0.0) {
                fade_opacity = 0.0;
            }*/










        }



       


       













      
      
        EndDrawing();
    }

    for (auto& tex : frames) {
        UnloadTexture(tex);
    }
    for (auto& tex : menuFrames) {
        UnloadTexture(tex);
    }

    UnloadMusicStream(bgMusic);
    CloseAudioDevice();
    CloseWindow();

    

	return 0;
}




//#include "raylib.h"
//#include <string>
//
//int main() {
//    const int screenWidth = 800;
//    const int screenHeight = 450;
//
//    InitWindow(screenWidth, screenHeight, "Character Name Input");
//
//    SetTargetFPS(60);
//
//    std::string name = "";          // Stores the entered name
//    int letterCount = 0;
//    int maxLetters = 20;           // Max character limit
//    bool nameEntered = false;
//
//    while (!WindowShouldClose()) {
//        if (!nameEntered) {
//            int key = GetCharPressed();
//
//            // Accept characters a-z, A-Z, 0-9, and basic symbols
//            while (key > 0) {
//                if ((key >= 32) && (key <= 125) && (letterCount < maxLetters)) {
//                    name += (char)key;
//                    letterCount++;
//                }
//                key = GetCharPressed();
//            }
//
//            // Backspace removes last character
//            if (IsKeyPressed(KEY_BACKSPACE) && !name.empty()) {
//                name.pop_back();
//                letterCount--;
//            }
//
//            // Enter key finishes input
//            if (IsKeyPressed(KEY_ENTER)) {
//                nameEntered = true;
//            }
//        }
//
//        BeginDrawing();
//        ClearBackground(RAYWHITE);
//
//        DrawText("Enter character name:", 100, 100, 30, DARKGRAY);
//        DrawRectangle(100, 140, 600, 40, LIGHTGRAY);  // input box
//        DrawText(name.c_str(), 110, 150, 20, BLACK);
//
//        if (nameEntered) {
//            DrawText("Name entered!", 100, 200, 30, GREEN);
//            DrawText(("Welcome, " + name + "!").c_str(), 100, 240, 30, MAROON);
//        }
//
//        EndDrawing();
//    }
//
//    CloseWindow();
//
//    return 0;
//}

//#include "raylib.h"
//#include <cstring>
//#include <iostream>
//#include<string>
//
//// Draws the maze using a 2D char array
//void DrawMaze(char** maze, int rows, int cols, int screenWidth, int screenHeight) {
//    float cellWidth = (float)screenWidth / cols;
//    float cellHeight = (float)screenHeight / rows;
//
//    for (int y = 0; y < rows; y++) {
//        for (int x = 0; x < cols; x++) {
//            Rectangle cellRect = {
//                x * cellWidth,
//                y * cellHeight,
//                cellWidth,
//                cellHeight
//            };
//
//            Color color;
//            switch (maze[y][x]) {
//            case '#': color = DARKGRAY; break;  // Wall
//            case ' ': color = RAYWHITE; break;  // Path
//            case 'S': color = GREEN; break;     // Start
//            case 'E': color = RED; break;       // End
//            default:  color = LIGHTGRAY; break; // Unknown
//            }
//
//            DrawRectangleRec(cellRect, color);
//        }
//    }
//}
//
//int main() {
//    const int screenWidth = 800;
//    const int screenHeight = 600;
//    InitWindow(screenWidth, screenHeight, "Maze Viewer");
//
//    // Define the maze as an array of strings (all must be same length)
//    const char* mazeData[] = {
//        "########",
//        "#S     #",
//        "# ### ##",
//        "#   #  #",
//        "### #E##",
//        "########"
//    };
//
//    int mazeRows = sizeof(mazeData) / sizeof(mazeData[0]);
//    int mazeCols = strlen(mazeData[0]);  // All rows must have same length
//
//    // Allocate dynamic char** array
//    char** maze = new char* [mazeRows];
//    for (int i = 0; i < mazeRows; i++) {
//        maze[i] = new char[mazeCols + 1]; // +1 for null terminator
//        strcpy(maze[i], mazeData[i]);
//    }
//
//    SetTargetFPS(60);
//
//    while (!WindowShouldClose()) {
//        BeginDrawing();
//        ClearBackground(BLACK);
//
//        DrawMaze(maze, mazeRows, mazeCols, screenWidth, screenHeight);
//
//        EndDrawing();
//    }
//
//    // Free dynamically allocated memory
//    for (int i = 0; i < mazeRows; i++) {
//        delete[] maze[i];
//    }
//    delete[] maze;
//
//    CloseWindow();
//    return 0;
//}


