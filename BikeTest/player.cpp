#include "player.h"
#include <iostream>

#include <raymath.h>
#include <rlgl.h>
#include "material.h"

void Player::init() {
	if (!this->isOnGround) {
		this->addVelocity(Vector2{ 0.0f, 0.2f });
	} else {
		if (this->velo.y > 0) this->setVelocity(Vector2{ 0, 0 });
	}

	this->addPos(this->velo);
	this->registerInput();

	if (this->isOnGround && !this->isMovingR && this->velo.x < 0) {
		this->addVelocity(Vector2{ this->friction.x, 0 }); 
		this->isMoving = true;
	}

	if (this->isOnGround && !this->isMovingL && this->velo.x > 0) {
		this->addVelocity(Vector2{ this->friction.y, 0 });
		this->isMoving = true;
	}

	if (this->velo.x == 0) {
		this->isMoving = false;
		this->velo.x = 0;
	}

	this->hitboxRec.x = this->x - 100;
	this->hitboxRec.y = this->y - 75;
}

void Player::render(float r) {
	/* old car
	DrawRectangle(this->x - 100, this->y - 75, 200, 100, GRAY);
	DrawRectangle(this->x + 25, this->y - 50, 60, 35, SKYBLUE);
	DrawCircle(this->x + 75, this->y+25, this->width / 2 + 5, LIGHTGRAY);
	DrawCircle(this->x - 75, this->y + 25, this->width / 2 + 5, LIGHTGRAY);
	*/
	// car
	this->rotation = Lerp(this->rotation, r, 0.1f);

	DrawTextureEx(this->texture, Vector2{this->x - 125, this->y - 75}, this->rotation, 1, WHITE);
	// render velo
	int sy = 500;
	int sx = 60;
	// x
	char xvelocity[500];
	sprintf_s(xvelocity, "%f", this->velo.x);
	DrawText(xvelocity, sx, sy, 32, WHITE);
	DrawText("X:", sx - 40, sy, 32, WHITE);
	// y
	char yvelocity[500];
	sprintf_s(yvelocity, "%f", this->velo.y);
	DrawText(yvelocity, sx, sy + 40, 32, WHITE);
	DrawText("Y:", sx - 40, sy + 40, 32, WHITE);
	// show trajectory
	if (this->showingTrajectory) {
		
		DrawTextureEx(this->arrow, Vector2{1100, 600}, this->trajectoryRot, 0.25, WHITE);
	}
	// debug hitbox draw
	//DrawRectangleLinesEx(this->hitboxRec, 2.5, BLUE);
}

void Player::setPos(Vector2 pos) {
	this->x = pos.x;
	this->y = pos.y;
}

void Player::addPos(Vector2 pos) {
	this->x += pos.x;
	this->y += pos.y;
}

void Player::addVelocity(Vector2 velo) {
	this->velo = Vector2{ this->velo.x + velo.x, this->velo.y + velo.y };
}

void Player::setVelocity(Vector2 velo) {
	this->velo = velo;
}

void Player::registerInput() {
	if (IsKeyDown(MOVE1) || IsKeyDown(MOVE1_2)) {
		if (this->velo.x < MAX_SPEED) {
			this->addVelocity(Vector2{ (float)0.1, 0 });
			this->isMovingR = true;
		} else {
			this->isMovingR = false;
		}
	} else {
		this->isMovingR = false;
	}

	if (IsKeyDown(MOVE2) || IsKeyDown(MOVE2_2)) {
		if (this->velo.x > -MAX_SPEED) {
			this->addVelocity(Vector2{ (float)-0.1, 0 });
			this->isMovingL = true;
		} else {
			this->isMovingL = false;
		}
	} else {
		this->isMovingL = false;
	}

	// reseting the player
	switch (GetKeyPressed()) {
	case RESET1:
		this->reset();
		break;
	case RESET2:
		this->reset();
		break;
	case RESET3:
		this->reset();
		break;
	case TOGGLE_TRAJECTORY_ARROW:
		this->showingTrajectory = !showingTrajectory;
		break;
	default:
		break;
	}
}

void Player::reset() {
	this->setPos(this->startingPos);
	this->setVelocity(Vector2{ 0, 0 });
}

void Player::setFriction(Vector2 f) {
	this->friction = f;
}

Rectangle Player::getHitbox() {
	return this->hitboxRec;
}

Vector2 Player::getVelocity() {
	return this->velo;
}

void Player::setIsOnGround(bool isOnGround) {
	this->isOnGround = isOnGround;
}

void Player::setRotation(float r) {
	this->rotation = r;
}

void Player::unload() {
	UnloadTexture(this->texture);
	UnloadSound(this->crash);
	UnloadTexture(this->arrow);
}

void Player::pointToTrajectory() {
	float trajectory = -((this->x * (GetFrameTime())) * (this->y * (GetFrameTime())));
	this->trajectoryRot = trajectory;
}

void Player::playCrash() {
	if (!IsSoundPlaying(this->crash)) PlaySound(this->crash);
	this->pointToTrajectory();
}

void Player::setTexture(Texture2D texture) {
	this->texture = texture;
	// loading other
	this->crash = LoadSound("sfx/crash.mp3");
	this->arrow = LoadTexture("textures/arrow.png");
}