#pragma once
#include <raylib.h>

#define MOVE1 KEY_D
#define MOVE1_2 KEY_RIGHT
#define MOVE2 KEY_A
#define MOVE2_2 KEY_LEFT

#define RESET1 KEY_R
#define RESET2 KEY_SPACE
#define RESET3 KEY_ENTER

#define TOGGLE_TRAJECTORY_ARROW KEY_T

#define MAX_SPEED 18

class Player {
protected:
	float x;
	float y;
	Vector2 velo;
	Rectangle hitboxRec;

	Vector2 startingPos;

	float width;
	float height;

	Vector2 friction;
	bool isOnGround = false;

	bool isMovingL = false;
	bool isMovingR = false;
	bool isMoving = false;

	Texture2D texture;
	float rotation = 0;

	Sound crash;

	Texture2D arrow;

	bool showingTrajectory = false;
	float trajectoryRot = 0;
public:
	Player(float x, float y, float width, float height, Rectangle hitbox) {
		this->x = x;
		this->y = y;
		this->hitboxRec = hitbox;
		this->width = width;
		this->height = height;

		this->startingPos = Vector2{ x, y };
	}

	// initialize the player actions
	virtual void init();
	virtual void render(float r);
	virtual void setPos(Vector2 pos);
	virtual void addPos(Vector2 pos);
	virtual void addVelocity(Vector2 velo);
	virtual void setVelocity(Vector2 velo);
	virtual void registerInput();
	virtual void reset();
	virtual void setFriction(Vector2 f);
	virtual Vector2 getVelocity();
	virtual void setRotation(float r);
	virtual void playCrash();
	virtual void pointToTrajectory();

	// other funcs

	virtual Rectangle getHitbox();
	virtual void setIsOnGround(bool isOnGround);
	virtual void unload();
	virtual void setTexture(Texture2D texture);
	
	Player() = default;
};