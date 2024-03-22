#pragma once
#include <raylib.h>

#include "material.h"

class Wall {
protected:
	float x;
	float y;
	Vector2 knockback;

	Rectangle hitboxRec;
	Texture2D texture;
	CCMaterial material;
public:
	Wall(float x, float y, Rectangle hitbox, CCMaterial material) {
		this->x = x;
		this->y = y;
		this->hitboxRec = hitbox;
		this->material = material;
	}

	virtual void render();
	virtual void init();
	virtual Rectangle getHitbox();
	virtual Vector2 getKnockback();
	virtual CCMaterial getMaterial();

	virtual void unload();

	Wall() = default;
};