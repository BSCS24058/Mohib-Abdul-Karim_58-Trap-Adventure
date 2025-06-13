#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>
#include "MyStr.h"
#include "raylib.h"
#include "Entity.h"
#include "Animation.h"
#include <vector>

class Dungeon;

enum PlayerAnimStates {
    IDLE = 0,
    RIGHT,
    LEFT,
    UP,
    DOWN
};

class Player : public Entity {
private:
    MyStr Name;
    vector<Texture2D> PlayerTextures;
    int no_of_textures;
    //0--idle
    //1--running right
    //2--running left
    //3--upwards
    //4--downwards
    int health;
    int lives;
    Texture2D livesTexture;
    PlayerAnimStates currentAnimState;

public:
    Player(); 
    Player& operator=(const Player& other);

    MyStr getName() const;
    void setName(const MyStr& name);

    Texture2D getTexture(int idx) const;
    Texture2D getLivesTexture() const;

	void setCurrentAnimState(PlayerAnimStates state);


    int getHealth() const;
    int getLives() const;

    void setHealth(int h);
    void setLives(int l);

    void takeDamage(int damage);
    void printStatus() const;

    void UpdatePosition(float dx, float dy, const Dungeon* dungeon);

    void DrawPlayer(const Animation& anim, const Vector2& position, float cellSize) const;

    ~Player(); 
};

#endif

