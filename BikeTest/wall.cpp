#include "wall.h"

void Wall::render() {
	DrawTextureEx(this->texture, Vector2{this->x, this->y}, 0, 1, WHITE);
	// debug hitbox draw
	//DrawRectangleLinesEx(this->hitboxRec, 3.5, WHITE);
}

void Wall::init() {
	if (this->material == CCMaterial::Brick) {
		this->texture = LoadTexture("textures/brick_mat.png");
		this->knockback = Vector2{ 2, -2 };
	}
}

Rectangle Wall::getHitbox() {
	return this->hitboxRec;
}

Vector2 Wall::getKnockback() {
	return this->knockback;
}

CCMaterial Wall::getMaterial() {
	return this->material;
}

void Wall::unload() {
	UnloadTexture(this->texture);
}