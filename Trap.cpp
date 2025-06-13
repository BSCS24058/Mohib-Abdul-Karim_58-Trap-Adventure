#include "Trap.h"
#include "raylib.h"

Trap::Trap() : resetTime{ 1.0f }, timeGapBetweenTrigger{ 1.0f }, timer{0.0f}, animPlaying{true}, animForward{true} {
    Obstacle_texture = LoadTexture("C:/Github Repositories/Trap-Adventure-Game/Spike.png");
    anim.frameCount = 4;
    anim.currentFrame = 0;
    anim.frameDuration = 0.15f;
    anim.elapsedTime = 0.0f;
}

Trap::Trap(float x, float y) : resetTime{ 1.0f }, timeGapBetweenTrigger{ 1.0f }, timer{0.0f}, animPlaying{true}, animForward{true} {
    position = { x, y };
    IsActive = true;
    Obstacle_texture = LoadTexture("C:/Github Repositories/Trap-Adventure-Game/Spike.png");
    anim.frameCount = 4;
    anim.currentFrame = 0;
    anim.frameDuration = 0.15f;
    anim.elapsedTime = 0.0f;
}

void Trap::Update(float deltaTime) {
    if (animPlaying) {
        anim.elapsedTime += deltaTime;
        if (anim.elapsedTime >= anim.frameDuration) {
            anim.elapsedTime = 0.0f;
            if (animForward) {
                anim.currentFrame++;
                if (anim.currentFrame >= anim.frameCount) {
                    anim.currentFrame = anim.frameCount - 1;
                    animPlaying = false;
                    timer = 0.0f;
                }
            } 
            else {
                if (anim.currentFrame > 0)
                    anim.currentFrame--;
                if (anim.currentFrame == 0) {
                    animPlaying = false;
                    timer = 0.0f;
                }
            }
        }
    } 
    else {
        timer += deltaTime;
        if (timer >= (animForward ? resetTime : timeGapBetweenTrigger)) {
            animPlaying = true;
            animForward = !animForward;
            timer = 0.0f;
        }
    }
}

void Trap::DrawTrap(float cellSize) const {
    if (!IsActive) return; 

    int frameWidth = Obstacle_texture.width / anim.frameCount;
    int frameHeight = Obstacle_texture.height;

    Rectangle sourceRect = {
        (float)(anim.currentFrame * frameWidth),
        0.0f,
        (float)(frameWidth),
        (float)(frameHeight)
    };

    Rectangle destRect = {
        position.x,
        position.y,
        cellSize,
        cellSize
    };

    DrawTexturePro(Obstacle_texture, sourceRect, destRect, { 0, 0 }, 0.0f, WHITE);
}







