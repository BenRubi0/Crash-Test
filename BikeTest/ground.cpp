#include "ground.h"



void Ground::render() {
	DrawRectangle(this->x, this->y, this->width, this->height, GRAY);
	// debug hitbox draw
	//DrawRectangleLinesEx(this->hitboxRec, 5, BLUE);
}

Rectangle Ground::getHitbox() {
	return this->hitboxRec;
}

Vector2 Ground::getFriction() {
	return this->friction;
}

void Ground::init() {
}

void Ground::unload() {
}