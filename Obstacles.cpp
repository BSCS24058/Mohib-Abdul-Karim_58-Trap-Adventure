#include"Obstacles.h"


Obstacles::Obstacles() : damagePoints{0.0} {}

Obstacles::Obstacles(float d){
	damagePoints = d;
}

void Obstacles::setDamagePoints(float damage) {
	damagePoints = damage;
}
float Obstacles::getDamagePoints() const {
	return damagePoints;
}

Texture2D Obstacles::getObstacleTexture() const{
	return Texture2D();
}
