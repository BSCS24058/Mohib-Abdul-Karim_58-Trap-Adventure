//#include "Trap.h"
//#include "raylib.h"
//
//Trap::Trap() : resetTime{0.0f}, timeSinceTriggered{0.0f}, frameWidth(0), frameHeight(0) {}
//
//Trap::Trap(float d, float ResTime, Vector2 pos, float size, int frameW, int frameH)
//    : Obstacles(d), resetTime(ResTime), timeSinceTriggered(0.0f), frameWidth(frameW), frameHeight(frameH)
//{
//    position = pos;
//    this->size = size;
//    Obstacle_texture = LoadTexture("C:/Github Repositories/Trap-Adventure-Game/Spike.png");
//    anim.frameCount = 4;
//    anim.currentFrame = 0;
//    anim.frameDuration = 0.15f;
//    anim.elapsedTime = 0.0f;
//}
//
//void Trap::Update(float deltaTime) {
//    animation_update(&anim, deltaTime);
//}
//
//void Trap::DrawTrap() const {
//    if (IsActive) {
//        Rectangle src = animation_get_current_frame_rect(&anim, 4, frameWidth, frameHeight);
//        Rectangle dest = { position.x, position.y, size, size };
//        DrawTexturePro(Obstacle_texture, src, dest, {0,0}, 0.0f, WHITE);
//    }
//}
//
//void Trap::SetPosition(Vector2 pos) {
//    position = pos;
//}
//
