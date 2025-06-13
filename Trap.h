#ifndef TRAP_H
#define TRAP_H

#include"Obstacles.h"

class Trap : public Obstacles {
	float resetTime;
	float timeSinceTriggered;
public:
	Trap(float x, float y, float width, float height, float resetTime = 5.0f)
		: Obstacles(x, y, width, height), resetTime(resetTime), timeSinceTriggered(0.0f) {}
	void update(float deltaTime) override {
		if (isTriggered()) {
			timeSinceTriggered += deltaTime;
			if (timeSinceTriggered >= resetTime) {
				reset();
			}
		}
	}
	void trigger() {
		timeSinceTriggered = 0.0f;
	}
	bool isTriggered() const {
		return timeSinceTriggered < resetTime;
	}
	void reset() {
		timeSinceTriggered = 0.0f;
	}
	virtual ~Trap() {}
};


#endif