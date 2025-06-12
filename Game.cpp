#include "Game.h"

Game* Game::instance = nullptr;

Game::Game() : no_of_levels{0}, current_level{0}, player{nullptr} {}

Game* Game::getInstance() {
    if (instance == nullptr) {
        instance = new Game();
    }
    return instance;
}

const vector<Level>& Game::getLevels() const {
    return levels;
}

int Game::getNoOfLevels() const {
    return no_of_levels;
}

int Game::getCurrentLevel() const {
    return current_level;
}

Player* Game::getPlayer() const {
    return player;
}

void Game::setNoOfLevels(int no_of_levels) {
    no_of_levels = no_of_levels;
}

void Game::setCurrentLevel(int current_level) {
    current_level = current_level;
}

void Game::setPlayer(Player* player_) {
    player = player_;
}
