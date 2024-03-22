#pragma once
#include <raylib.h>

#include "player.h"

class Ground {
protected:
	float x;
	float y;
	float width;
	float height;
	Rectangle hitboxRec;

	Vector2 friction;
public:
	Ground(float x, float y, float width, float height, Vector2 friction, Rectangle hitbox) {
		this->x = x;
		this->y = y;
		this->width = width;
		this->height = height;
		this->hitboxRec = hitbox;
		this->friction = friction;
	}

	virtual void init();
	virtual void render();
	virtual Rectangle getHitbox();
	virtual Vector2 getFriction();

	// unloading the texture
	virtual void unload();

	Ground() = default;
};