#include "Player.h"

#include "Player.h"
#include <utility> 

Player::Player() : Name(""), health(100), lives(3), position(0) {}

Player::Player(const MyStr& name, int h, int l, int pos)
    : Name(name), health(h), lives(l), position(pos) {
}

Player::Player(const Player& other)
    : Name(other.Name), health(other.health), lives(other.lives), position(other.position) {
}



Player::~Player() = default;

Player& Player::operator=(const Player& other) {
    if (this != &other) {
        Name = other.Name;
        health = other.health;
        lives = other.lives;
        position = other.position;
    }
    return *this;
}


MyStr Player::getName() const { return Name; }
int Player::getHealth() const { return health; }
int Player::getLives() const { return lives; }
int Player::getPosition() const { return position; }

void Player::setName(const MyStr& name) { Name = name; }
void Player::setHealth(int h) { health = h; }
void Player::setLives(int l) { lives = l; }
void Player::setPosition(int pos) { position = pos; }

void Player::takeDamage(int damage) {
    health -= damage;
    if (health <= 0) {
        lives--;
        health = 100; 
    }
}

void Player::move(int delta) {
    position += delta;
}

void Player::printStatus() const {
    std::cout << "Name: " << Name << "\n"
        << "Health: " << health << "\n"
        << "Lives: " << lives << "\n"
        << "Position: " << position << std::endl;
}

