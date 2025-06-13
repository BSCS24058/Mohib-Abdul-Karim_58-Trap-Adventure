#ifndef OBSTACLES_H
#define OBSTACLES_H

#include"Entity.h"
#include"raylib.h"


class Obstacles : public Entity {
	Texture2D Obstacle_texture;
	float damagePoints;

public:
	Obstacles(const char* texturePath, Vector2 position, float damagePoints = 10.0f);
	void setDamagePoints(float damage);
	float getDamagePoints() const;
};

#endif
