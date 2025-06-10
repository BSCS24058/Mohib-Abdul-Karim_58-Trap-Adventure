#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>
#include "MyStr.h"

class Player {
private:
    MyStr Name;
    int health;
    int lives;
    int position;

public:
   
    Player(); 
    Player(const MyStr& name, int h, int l, int pos);  
    Player(const Player& other); 

    
    Player& operator=(const Player& other);

    
    MyStr getName() const;
    int getHealth() const;
    int getLives() const;
    int getPosition() const;

    
    void setName(const MyStr& name);
    void setHealth(int h);
    void setLives(int l);
    void setPosition(int pos);

    void takeDamage(int damage);
    void move(int delta);
    void printStatus() const;


    ~Player(); 
};

#endif

