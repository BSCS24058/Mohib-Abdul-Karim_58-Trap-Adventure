#ifndef GAME_H
#define GAME_H

#include<iostream>
#include<vector>
#include"Level.h"
#include"Player.h"

using namespace std;

class Game {
    vector<Level> levels;
    int no_of_levels;
    int current_level;

    Player* player;

    static Game* instance;

    Game();

    Game(const Game&) = delete;
    Game& operator=(const Game&) = delete;

public:
    static Game* getInstance();

    // Getters
    const vector<Level>& getLevels() const;
    int getNoOfLevels() const;
    int getCurrentLevel() const;
    Player* getPlayer() const;

    // Setters
    void setLevels(const vector<Level>& levels);
    void setNoOfLevels(int no_of_levels);
    void setCurrentLevel(int current_level);
    void setPlayer(Player* player);
};

#endif // !GAME_H

