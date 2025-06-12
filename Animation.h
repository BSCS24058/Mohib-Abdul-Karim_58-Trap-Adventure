#ifndef ANIMATION_H
#define ANIMATION_H

#include <raylib.h>

typedef struct Animation {
	int frameCount;      
	int currentFrame;    
	float frameDuration; 
	float elapsedTime;   
} Animation;

void animation_update(Animation* anim, float deltaTime);

Rectangle animation_get_current_frame_rect(const Animation* anim, int num_of_frames_per_row, int frame_width, int frame_height);
#endif 

