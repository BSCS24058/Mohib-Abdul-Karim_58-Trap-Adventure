#ifndef ANIMATION_H
#define ANIMATION_H

#include <raylib.h>

typedef struct Animation {
	int frameCount;      // Number of frames in the animation
	int currentFrame;    // Current frame index
	float frameDuration; // Duration of each frame in seconds
	float elapsedTime;   // Time elapsed since the last frame change
} Animation;

void animation_update(Animation* anim, float deltaTime) {
	if (anim == nullptr) return; // Check for null pointer
	anim->elapsedTime += deltaTime; // Update elapsed time
	// Check if it's time to switch to the next frame
	if (anim->elapsedTime >= anim->frameDuration) {
		anim->currentFrame = (anim->currentFrame + 1) % anim->frameCount; // Loop back to the first frame
		anim->elapsedTime = 0.0f; // Reset elapsed time
	}
}

Rectangle animation_get_current_frame_rect(const Animation* anim, int num_of_frames_per_row, int frame_width, int frame_height) {
	float x = (anim->currentFrame % num_of_frames_per_row) * frame_width;
	float y = (anim->currentFrame / num_of_frames_per_row) * frame_height;

	return Rectangle{ x, y, static_cast<float>(frame_width), static_cast<float>(frame_height) };
}

#endif // !ANIMATION_H

