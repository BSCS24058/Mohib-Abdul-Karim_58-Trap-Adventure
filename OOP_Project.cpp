#include<iostream>
#include"raylib.h"
#include<vector>
#include<iomanip>
#include<sstream>
#include"MyStr.h"
#include"button.hpp"
//#include <thread>
//#include <atomic>
#include "Player.h"
#include"Level.h"
//#include"Dungeon.h"
#include"fstream"
#include"Globals.h"
#include"Animation.h"
#include"Game.h"

#define TOTAL_TITLE_FRAMES 200
#define TOTAL_MENU_FRAMES 317
#define FRAME_RATE 60

using namespace std;

vector<Texture2D> frames;
vector<Texture2D> menuFrames;
//atomic<bool> framesLoaded(false);


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

void LoadTitleFrames() {
    for (int i = 0; i < TOTAL_TITLE_FRAMES; i++) {
        MyStr path = GetTitlePath(i);
        Image img = LoadImage(path.fetchstr());
        frames.push_back(LoadTextureFromImage(img));
        UnloadImage(img);
    }
}
void LoadMenuFrames() {
    for (int i = 0; i < TOTAL_MENU_FRAMES; i++) {
        MyStr path = GetMenuPath(i);
        Image img = LoadImage(path.fetchstr());
        menuFrames.push_back(LoadTextureFromImage(img));
        UnloadImage(img);
    }
}

//void LoadAllFrames() {
//    thread titlethread(LoadTitleFrames);
//    thread menuthread(LoadMenuFrames);
//    titlethread.join();
//    menuthread.join();
//    framesLoaded = true;
//}

enum GameStates {
    Loading,
    Title,
    Title_To_Menu,
    Menu,
    Menu_To_PreStart,
    PreStart,
    Difficulty_Selection,
    Loading_Level_1,
	Level_1,
};


bool startfade = false;
bool enterReleasedAfterName = false;


// Screen dimensions(Globals)
const int screenWidth = 1280;
const int screenHeight = 720;



int main() {

    InitWindow(screenWidth, screenHeight, "Trap Adventure");
    SetTargetFPS(FRAME_RATE);



    //===============INITIALIZE GAME(Singleton class)============================================

    Game::getInstance()->initializeLevels(3); // Three levels for now
    Game::getInstance()->setCurrentLevel(0);  // Starting from level 0(or 1 in generlaized labels)

    Player PL1;

	Game::getInstance()->setPlayer(&PL1);

    {
        ifstream levelFile("Level1.txt");
        if (levelFile.is_open()) {
            Game::getInstance()->getLevels()[0].LoadDungeon(levelFile, &PL1);
            levelFile.close();
        }
        else {
            cerr << "Failed to open Level1.txt" << endl;
        }
    }

    //===========================================================================================

    //thread loader(LoadAllFrames);

    LoadTitleFrames();
    LoadMenuFrames();
	//framesLoaded = true;



	//audio initialization-------------------------------
    InitAudioDevice();
    Music bgMusic = LoadMusicStream("C:/Users/User/Downloads/Music/Little Nightmares 2 OST Track 1 - Little Nightmares II Main Theme_2.mp3");   // For background music
    PlayMusicStream(bgMusic);
    bgMusic.looping = true;
    //------------------------------------------------------------

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

    //For level 1 Loading
    float loadingLevel1Timer = 0.0f;

    // ===== Title Screen Buttons =============================================
    float titleButtonScale = 0.3f;
    Texture2D tempTex = LoadTexture("C:/Github Repositories/Trap-Adventure-Game/Buttons/End_Button.png");
    int titleButtonWidth = tempTex.width * titleButtonScale;
    int titleButtonHeight = tempTex.height * titleButtonScale;
    UnloadTexture(tempTex);

    Vector2 startMenuButtonPos = { (float)(screenWidth - titleButtonWidth) / 2, (float)(screenHeight / 2 - 325) };
    Vector2 exitMenuButtonPos = { (float)(screenWidth - titleButtonWidth) / 2, (float)(screenHeight / 2 - 100) };

    Button startMenuButton{"C:/Github Repositories/Trap-Adventure-Game/Buttons/Start_Button (3).png", startMenuButtonPos, titleButtonScale };
    Button exitMenuButton{ "C:/Github Repositories/Trap-Adventure-Game/Buttons/End_Button.png", exitMenuButtonPos, titleButtonScale };
    //======================================================================================================



    // ===== Difficulty Selection Buttons ==================================================================
    float difficultyButtonScale = 0.4f;
    int buttonSpacing = 60;

    tempTex = LoadTexture("C:/Github Repositories/Trap-Adventure-Game/Buttons/Noob_Button.jpg");
    int difficultyButtonWidth = tempTex.width * difficultyButtonScale;
    int difficultyButtonHeight = tempTex.height * difficultyButtonScale;
    UnloadTexture(tempTex);

    float centerX = (float)(screenWidth - difficultyButtonWidth) / 2;

    Vector2 noobButtonPos = { centerX, (float)(screenHeight / 2 - difficultyButtonHeight - buttonSpacing) };
    Vector2 proButtonPos = { centerX, (float)(screenHeight / 2) };
    Vector2 hardcoreButtonPos = { centerX, (float)(screenHeight / 2 + difficultyButtonHeight + buttonSpacing) };

    Button NoobButton{ "C:/Github Repositories/Trap-Adventure-Game/Buttons/Noob_Button.jpg", noobButtonPos, difficultyButtonScale };
    Button ProButton{ "C:/Github Repositories/Trap-Adventure-Game/Buttons/Pro_Button.jpg", proButtonPos, difficultyButtonScale };
    Button HardcoreButton{ "C:/Github Repositories/Trap-Adventure-Game/Buttons/Hardcore_Button.jpg", hardcoreButtonPos, difficultyButtonScale };
	//======================================================================================================


    //Player declaration and info prompt----------------------------------------

    MyStr name = "";
    int letterCount = 0;
    int maxLetters = 20;
    bool nameEntered = false;
    //--------------------------------------------------


    // Player Animation===========================================================

    Animation playerAnim;
    playerAnim.frameCount = 4;        
    playerAnim.currentFrame = 0;      
    playerAnim.frameDuration = 0.15f;  
    playerAnim.elapsedTime = 0.0f;     

    //============================================================================

    bool exit = false;

    while (!WindowShouldClose() && exit == false) {

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
            /* case Loading: {

                 if ((GetTime() * 2) - (int)(GetTime() * 2) < 1)
                     DrawText("Loading...",
                         (screenWidth - MeasureText("Loading...", 40)) / 2,
                         (screenHeight - 40) / 2, 40, WHITE);

                 if (framesLoaded) Current_State = Title;
                 break;
             }*/

        case Title: {
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
        }

        case Title_To_Menu: {
            DrawTexture(frames[currentFrame], 0, 0, WHITE);

            fade_opacity += GetFrameTime() / 2;
            if (fade_opacity >= 1.0) {
                fade_opacity = 1.0;
                Current_State = Menu;
            }

            DrawRectangle(0, 0, screenWidth, screenHeight, Fade(BLACK, fade_opacity));
            break;

        }

        case Menu: {
            ClearBackground(BLACK);
            fade_opacity -= GetFrameTime() / 2;
            if (fade_opacity <= 0.0) {
                fade_opacity = 0.0;
            }

            DrawTexture(menuFrames[menuCurrentFrame], 0, 0, WHITE);
            startMenuButton.Draw();
            exitMenuButton.Draw();
            DrawRectangle(0, 0, screenWidth, screenHeight, Fade(BLACK, fade_opacity));

            Vector2 mousePosition = GetMousePosition();
            bool mousePressed = IsMouseButtonPressed(MOUSE_BUTTON_LEFT);

            if (startMenuButton.isPressed(mousePosition, mousePressed))
            {
                Current_State = Menu_To_PreStart;
            }

            if (exitMenuButton.isPressed(mousePosition, mousePressed))
            {
                exit = true;
            }
            break;
        }

        case Menu_To_PreStart: {

            DrawTexture(menuFrames[menuCurrentFrame], 0, 0, WHITE);
            fade_opacity += GetFrameTime() / 2;
            if (fade_opacity >= 1.0) {
                fade_opacity = 1.0;
                Current_State = PreStart;
            }

            DrawRectangle(0, 0, screenWidth, screenHeight, Fade(BLACK, fade_opacity));
            break;

        }

        case PreStart: {

            ClearBackground(BLACK);

            if (!nameEntered) {

                fade_opacity -= GetFrameTime() / 2;
                if (fade_opacity <= 0.0) {
                    fade_opacity = 0.0;
                }
                int key = GetCharPressed();

                while (key > 0) {
                    if ((key >= 32) && (key <= 125) && (letterCount < maxLetters)) {
                        name.push_back((char)key);
                        letterCount++;
                    }
                    key = GetCharPressed();
                }

                if (IsKeyPressed(KEY_BACKSPACE) && !name.empty()) {
                    name.pop_back();
                    letterCount--;
                }

                if (IsKeyPressed(KEY_ENTER)) {
                    nameEntered = true;
                    enterReleasedAfterName = false; 
                }
            }
            else {
                if (!IsKeyDown(KEY_ENTER)) {
                    enterReleasedAfterName = true;
                }
                if (enterReleasedAfterName && IsKeyPressed(KEY_ENTER) && !startfade) {
                    startfade = true;
                }
            }

            ClearBackground(BLACK);

            const char* prompt = "Enter Player name:";
            int promptFontSize = 40;
            int promptX = (GetScreenWidth() - MeasureText(prompt, promptFontSize)) / 2;
            int promptY = (GetScreenHeight() / 2) - 100;

            int boxWidth = 500;
            int boxHeight = 60;
            int boxX = (GetScreenWidth() - boxWidth) / 2;
            int boxY = (GetScreenHeight() / 2) - 20;

            DrawText(prompt, promptX, promptY, promptFontSize, YELLOW);

            DrawRectangle(boxX, boxY, boxWidth, boxHeight, SKYBLUE);
            DrawRectangle(boxX + 4, boxY + 4, boxWidth - 8, boxHeight - 8, RAYWHITE);

            if (!name.empty()) {
                DrawText(name.fetchstr(), boxX + 16, boxY + (boxHeight - 30) / 2, 30, DARKBLUE);
            }

            if (nameEntered) {
                PL1.setName(name);

                MyStr welcome = "Welcome, " + MyStr(name.fetchstr()) + "!";
                int welcomeFontSize = 40;
                int welcomeWidth = MeasureText(welcome.fetchstr(), welcomeFontSize);
                DrawText(welcome.fetchstr(), (GetScreenWidth() - welcomeWidth) / 2, boxY + boxHeight + 40, welcomeFontSize, ORANGE);

                MyStr PressEnt = "Press Enter To Continue";
                int PressEntFontSize = 40;
                int  PressEntWidth = MeasureText(PressEnt.fetchstr(), PressEntFontSize);
                DrawText(PressEnt.fetchstr(), (GetScreenWidth() - PressEntWidth) / 2, boxY + boxHeight + 90, PressEntFontSize, ORANGE);
            }

            if (startfade && nameEntered) {
                fade_opacity += GetFrameTime() / 2;
                if (fade_opacity >= 1.0) {
                    fade_opacity = 1.0;
                    Current_State = Difficulty_Selection;
                    startfade = false; 
                }
            }

            DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), Fade(BLACK, fade_opacity));
            break;
        }

        case Difficulty_Selection: {
            ClearBackground(BLACK);
            fade_opacity -= GetFrameTime() / 2;
            if (fade_opacity <= 0.0) {
                fade_opacity = 0.0;
            }
            DrawText("Difficulty Selection", (GetScreenWidth() - MeasureText("Difficulty Selection", 70)) / 2, (GetScreenHeight() / 2) - 300, 70, YELLOW);
            NoobButton.Draw();
            ProButton.Draw();
            HardcoreButton.Draw();
            DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), Fade(BLACK, fade_opacity));

            Vector2 mousePosition = GetMousePosition();
            bool mousePressed = IsMouseButtonPressed(MOUSE_BUTTON_LEFT);

            if (NoobButton.isPressed(mousePosition, mousePressed)) {
                Current_State = Loading_Level_1;
                loadingLevel1Timer = 0.0f; 
            }

            break;
        }

        case Loading_Level_1: {
            ClearBackground(BLACK);
            DrawText("Loading Level 1...", (GetScreenWidth() - MeasureText("Loading Level 1...", 40)) / 2, (GetScreenHeight() - 40) / 2, 40, WHITE);

            loadingLevel1Timer += GetFrameTime();
            if (loadingLevel1Timer >= 3.0f) {
                Current_State = Level_1;
            }
            break;
        }

        case Level_1: {
            ClearBackground(BLACK);
            float deltaTime = GetFrameTime();
            animation_update(&playerAnim, deltaTime);
			Game::getInstance()->getLevels()[0].DrawLevel();

            float cellSize = Game::getInstance()->getLevels()[0].getDungeon()->GetCellSize();

            float moveSpeed = 100.f;

            if (IsKeyDown(KEY_RIGHT)) { 
                Game::getInstance()->getPlayer()->setCurrentAnimState(RIGHT);
				Game::getInstance()->getPlayer()->UpdatePosition(moveSpeed* deltaTime, 0);
                Game::getInstance()->getPlayer()->DrawPlayer(playerAnim, Game::getInstance()->getPlayer()->GetPosition(), cellSize);
            }
            else if (IsKeyDown(KEY_LEFT)) { 
                Game::getInstance()->getPlayer()->setCurrentAnimState(LEFT);
				Game::getInstance()->getPlayer()->UpdatePosition(-moveSpeed * deltaTime, 0);
                Game::getInstance()->getPlayer()->DrawPlayer(playerAnim, Game::getInstance()->getPlayer()->GetPosition(), cellSize);
            }
            else if (IsKeyDown(KEY_UP)) {
                Game::getInstance()->getPlayer()->setCurrentAnimState(UP);
                Game::getInstance()->getPlayer()->UpdatePosition(0, -moveSpeed * deltaTime);
                Game::getInstance()->getPlayer()->DrawPlayer(playerAnim, Game::getInstance()->getPlayer()->GetPosition(), cellSize);
            }
            else if (IsKeyDown(KEY_DOWN)) {
                Game::getInstance()->getPlayer()->setCurrentAnimState(DOWN);
                Game::getInstance()->getPlayer()->UpdatePosition(0, moveSpeed * deltaTime);
                Game::getInstance()->getPlayer()->DrawPlayer(playerAnim, Game::getInstance()->getPlayer()->GetPosition(), cellSize);
            }
            else { 
                Game::getInstance()->getPlayer()->setCurrentAnimState(IDLE);
                Game::getInstance()->getPlayer()->DrawPlayer(playerAnim, Game::getInstance()->getPlayer()->GetPosition(), cellSize);
            }

            Game::getInstance()->getPlayer()->DrawPlayer(playerAnim, Game::getInstance()->getPlayer()->GetPosition(), cellSize);

            Game::getInstance()->getPlayer()->printStatus();

            break;
        }

        }

        EndDrawing();
    }

        //if (loader.joinable()) loader.join();    


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













