#ifndef ANIMATION_H
#define ANIMATION_H

#include <raylib.h>

typedef struct Animation {
	int frameCount;      
	int currentFrame;    
	float frameDuration; 
	float elapsedTime;   
} Animation;

void animation_update(Animation* anim, float deltaTime) {
	if (anim == nullptr) return; 
	anim->elapsedTime += deltaTime; 
	
	if (anim->elapsedTime >= anim->frameDuration) {
		anim->currentFrame = (anim->currentFrame + 1) % anim->frameCount; 
		anim->elapsedTime = 0.0f; 
	}
}

Rectangle animation_get_current_frame_rect(const Animation* anim, int num_of_frames_per_row, int frame_width, int frame_height) {
	float x = (anim->currentFrame % num_of_frames_per_row) * frame_width;
	float y = (anim->currentFrame / num_of_frames_per_row) * frame_height;

	return Rectangle{ x, y, static_cast<float>(frame_width), static_cast<float>(frame_height) };
}

#endif 

