#include <raylib.h>

#include <iostream>

#include "game.h"

int main() {
	InitWindow(1500, 900, "Crash test");
	InitAudioDevice();
	SetTargetFPS(60);

	game::_init();
	std::cout << GetWorkingDirectory();

	while (!WindowShouldClose()) {
		// actions

		game::init();

		// rendering
		BeginDrawing();
		ClearBackground(SKYBLUE);

		game::render();

		EndDrawing();
	}

	game::unload();

	CloseWindow();

	return 0;
}