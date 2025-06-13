#ifndef ENTITY_H
#define ENTITY_H

#include<vector>
#include"raylib.h"

class Entity {
protected:
    Vector2 position;
    bool IsActive;
    float size;
public:
	Entity() : position({ 0, 0 }), IsActive(true), size(1.0f) {}
    Entity(Vector2 pos, float s) : position(pos), IsActive(true), size(s) {}
    virtual ~Entity() = default;


    void SetActive(bool active) { IsActive = active; }
    bool IsEntityActive() const { return IsActive; }
    Vector2 GetPosition() const { return position; }
    float GetSize() const { return size; }
    void SetPosition(int x, int y) { position = { (float)(x), (float)(y) }; }
};

#endif // !ENTITY_H

