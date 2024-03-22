#pragma once
#include <raylib.h>

#include "player.h"
#include "ground.h"
#include "wall.h"

namespace game {
	// global variables
	Player player(1500/2, 900 / 2, 50, 50, Rectangle{1500 / 2, 900 / 2, 200, 125});
	Ground ground(0, 850, 1500, 100, /* friction */ Vector2{(float)0.02, (float) - 0.02}, Rectangle{0, 850, 1500, 100});
	Wall wall(1200, 550, Rectangle{1200, 550, 200, 300}, CCMaterial::Brick);

	float global_rotation = 0;

	bool keysHaveBeenPressed = false;

	// render game
	inline void render() {
		// text

		DrawFPS(20, 20);

		if (IsKeyPressed(KEY_R) || IsKeyPressed(KEY_SPACE) || IsKeyPressed(KEY_ENTER) 
			|| IsKeyPressed(KEY_A) || IsKeyPressed(KEY_LEFT) 
			|| IsKeyPressed(KEY_RIGHT) || IsKeyPressed(KEY_D) 
			|| IsKeyPressed(KEY_T)) {
			keysHaveBeenPressed = true;
		}

		if (!keysHaveBeenPressed) {
			DrawText("R to reset (or you can use enter or space).", 20, 800, 30, WHITE);
			DrawText("A and D to move left and right (or left and right arrow).", 20, 750, 30, WHITE);
			DrawText("Press T to toggle arrow trajectory.", 20, 700, 30, WHITE);
		}

		// objects
		ground.render();
		player.render(global_rotation);
		wall.render();
	}

	// init game actions
	inline void init() {
		player.init();
		// collider with the ground
		bool cPAG = CheckCollisionRecs(player.getHitbox(), ground.getHitbox());
		if (cPAG) {
			player.setIsOnGround(true);
			player.setFriction(ground.getFriction());
			player.addVelocity(Vector2{ 0, -0.4 });
		} else {
			player.setIsOnGround(false);
			player.setFriction(Vector2{0,0});
		}
		// collider with wall
		bool cPAW = CheckCollisionRecs(player.getHitbox(), wall.getHitbox());
		if (cPAW) {
			player.setIsOnGround(false);
			player.setFriction(Vector2{ 0, 0 });
			player.addVelocity(Vector2{ -(player.getVelocity().x * wall.getKnockback().x), (player.getVelocity().x / wall.getKnockback().y) });
			global_rotation = player.getVelocity().x * 2;
			player.playCrash();
		}
		// rotation
		if (global_rotation < 0) global_rotation++;
		if (global_rotation > 0) global_rotation--;
	}

	// init static actions
	inline void _init() {
		ground.init();
		player.setTexture(LoadTexture("textures/car.png"));
		wall.init();
	}

	// unloading assets
	inline void unload() {
		ground.unload();
		player.unload();
		wall.unload();
	}
}