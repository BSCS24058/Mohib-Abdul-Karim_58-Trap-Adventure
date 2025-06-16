#include "Player.h"
#include "Animation.h" 
#include "Dungeon.h"
#include"Obstacles.h"
#include"Trap.h"

Player::Player() : Name(""), health(100), lives(3), TakingDamage(false), damageTimer(0.0f), damageTintTimer(0.0f) {
    PlayerTextures.resize(5);
    PlayerTextures[0] = LoadTexture("C:/Github Repositories/Trap-Adventure-Game/PlayerTextures/Player_Idle.png");
    PlayerTextures[1] = LoadTexture("C:/Github Repositories/Trap-Adventure-Game/PlayerTextures/Player_Walking_Right.png");
    PlayerTextures[2] = LoadTexture("C:/Github Repositories/Trap-Adventure-Game/PlayerTextures/Player_Walking_Left.png");
    PlayerTextures[3] = LoadTexture("C:/Github Repositories/Trap-Adventure-Game/PlayerTextures/Player_Walking_Up.png");
    PlayerTextures[4] = LoadTexture("C:/Github Repositories/Trap-Adventure-Game/PlayerTextures/Player_Walking_Down.png");

    livesTexture = LoadTexture("C:/Github Repositories/Trap-Adventure-Game/PlayerTextures/heart.png");
}




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
void Player::setName(const MyStr& name) { Name = name; }

Texture2D Player::getTexture(int idx) const {
    return PlayerTextures[idx];
}



int Player::getHealth() const { return health; }
void Player::setHealth(int h) { health = h; }


int Player::getLives() const { return lives; }
void Player::setLives(int l) { lives = l; }

Texture2D Player::getLivesTexture() const {
    return livesTexture;
}

void Player::setCurrentAnimState(PlayerAnimStates state){
	currentAnimState = state;
}




void Player::takeDamage(int damage) {
    health -= damage;
    if (health <= 0) {
        lives--;
        health = 100; 
    }
}

void Player::printStatus() const {
    int heartSize = 40;
    int heartSpacing = 10;
    int topMargin = 20;
    int leftMargin = 20;

    for (int i = 0; i < lives; ++i) {
        DrawTextureEx(
            livesTexture,
            Vector2{ (float)(leftMargin + i * (heartSize + heartSpacing)), (float)topMargin },
            0.0f,
            (float)heartSize / livesTexture.width,
            WHITE
        );
    }

    int healthBarWidth = 150;
    int healthBarHeight = 20;
    int healthBarX = leftMargin + lives * (heartSize + heartSpacing) + 20;
    int healthBarY = topMargin;
    float healthPercent = (float)health / 100.0f;

    DrawRectangle(healthBarX, healthBarY, healthBarWidth, healthBarHeight, GRAY);
    DrawRectangle(healthBarX, healthBarY, (int)(healthBarWidth * healthPercent), healthBarHeight, RED);

    DrawText(
        TextFormat("%d/100", health),
        healthBarX + healthBarWidth + 10,
        healthBarY,
        20,
        WHITE
    );
}

void Player::DrawPlayer(const Animation& anim, const Vector2& position, float cellSize) const {
    float scale = 0.8f;
    float playerSize = cellSize * scale;
    float offset = (cellSize - playerSize) / 2.0f;
    Vector2 drawPos = { position.x + offset, position.y + offset };

    Color tint = WHITE;
    if (damageTintTimer > 0.0f) {
        int blink = static_cast<int>(GetTime() * 5) % 2;
        if (blink == 0) {
            tint = RED;
        }
        else {
            tint = WHITE;
        }
    }

    if (currentAnimState == IDLE) {
        DrawTextureEx(getTexture(0), drawPos, 0.0f, playerSize / getTexture(0).width, tint);
        return;
    }
    else {
        Texture2D currentTexture = getTexture((int)(currentAnimState));
        int frameWidth = currentTexture.width / anim.frameCount;
        int frameHeight = currentTexture.height;
        Rectangle srcRect = animation_get_current_frame_rect(&anim, anim.frameCount, frameWidth, frameHeight);
        Rectangle destRect = { drawPos.x, drawPos.y, playerSize, playerSize };
        DrawTexturePro(currentTexture, srcRect, destRect, Vector2{ 0, 0 }, 0.0f, tint);
    }
}


void Player::UpdatePosition(float dx, float dy, const Dungeon* dungeon, const vector<Obstacles*>& obstacles) {

    damageTimer += GetFrameTime();

    float scale = 0.8f;
    float cellSize = dungeon->GetCellSize();
    float playerSize = cellSize * scale;
    float offset = (cellSize - playerSize) / 2.0f;

    float newX = position.x + dx;
    float newY = position.y + dy;

    float left = newX + offset;
    float top = newY + offset;
    float right = left + playerSize;
    float bottom = top + playerSize;

    float x_offset = dungeon->GetXOffset();
    float y_offset = dungeon->GetYOffset();

    int leftCol = (int)((left - x_offset) / cellSize);
    int rightCol = (int)((right - x_offset - 0.1f) / cellSize);
    int topRow = (int)((top - y_offset) / cellSize);
    int bottomRow = (int)((bottom - y_offset - 0.1f) / cellSize);

    if (dungeon->GetCell(leftCol, topRow) != 'W' && dungeon->GetCell(rightCol, topRow) != 'W'
        && dungeon->GetCell(leftCol, bottomRow) != 'W' && dungeon->GetCell(rightCol, bottomRow) != 'W') {
        position.x = newX;
        position.y = newY;
    }

    for (const auto& obs : obstacles) {
        Trap* trap = dynamic_cast<Trap*>(obs);
        if (trap && trap->IsDangerous()) {
            float trapX = trap->GetPosition().x;
            float trapY = trap->GetPosition().y;
            float trapSize = cellSize;

            float playerLeft = position.x + offset;
            float playerTop = position.y + offset;
            float playerRight = playerLeft + playerSize;
            float playerBottom = playerTop + playerSize;

            float trapLeft = trapX;
            float trapTop = trapY;
            float trapRight = trapX + trapSize;
            float trapBottom = trapY + trapSize;

            if (playerRight > trapLeft && playerLeft < trapRight &&
                playerBottom > trapTop && playerTop < trapBottom &&
                damageTimer >= 0.5f) {
                damageTimer = 0.0f;
                TakingDamage = true;
                damageTintTimer = 1.0f;
				this->takeDamage(50); 
                break;
            }
        }
    }

    if (damageTintTimer > 0.0f) {
        damageTintTimer -= GetFrameTime();
        if (damageTintTimer < 0.0f) {
            damageTintTimer = 0.0f;
        }
    }
}





Player::~Player() {
    for(auto& texture : PlayerTextures) {
        UnloadTexture(texture); 
    }
}