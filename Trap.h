#ifndef TRAP_H
#define TRAP_H

#include "Obstacles.h"
#include "Animation.h"

class Trap : public Obstacles {
    float resetTime;
    float timeGapBetweenTrigger;
    float timer;               
    bool animPlaying;          
    bool animForward; // true = forward, false = reverse
    Animation anim;
public:
    Trap();
    Trap(float x, float y); 
    void Update(float deltaTime);
    void DrawTrap(float cellSize) const;
};


#endif