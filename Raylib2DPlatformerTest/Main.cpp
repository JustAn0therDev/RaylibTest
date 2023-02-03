#include <iostream>
#include "raylib.h"

Camera3D globalCam{};

const int GLOBAL_CAM_DISTANCE_LIMIT = 60;
const int WIDTH = 600;
const int HEIGHT = 400;

void Update();

int main() {
	InitWindow(WIDTH, HEIGHT, "Title");

	SetTargetFPS(60);

	globalCam.position = { 0, 0, 0 };
	globalCam.target = { 2, 2, 2 };
	globalCam.up = { 0, 1, 0 };
	globalCam.fovy = 90;
	globalCam.projection = CAMERA_PERSPECTIVE;

	while (!WindowShouldClose())
	{
		Update();

		if (IsKeyDown(KEY_R)) {
			globalCam.position.z = 0;
			globalCam.position.y = 0;
		}
	}

	CloseWindow();

	return EXIT_SUCCESS;
}

void Update() {
	BeginDrawing();

	BeginMode3D(globalCam);

	ClearBackground(RAYWHITE);

	DrawGrid(10, 5.0f);

	Vector3 cubePos1 = { 0, 2.5f, 0 };

	DrawCube(cubePos1, 5.0f, 5.0f, 5.0f, DARKBLUE);

	EndMode3D();

	if (globalCam.position.z != -GLOBAL_CAM_DISTANCE_LIMIT) {
		globalCam.position.z -= 0.5f;
	}

	if (globalCam.position.y != GLOBAL_CAM_DISTANCE_LIMIT) {
		globalCam.position.y += 0.5f;
	}

	if ((int)globalCam.position.z == -GLOBAL_CAM_DISTANCE_LIMIT && (int)globalCam.position.y == GLOBAL_CAM_DISTANCE_LIMIT) {
		DrawText("NICE!", (WIDTH / 2) - 100, (HEIGHT / 2) - 40, 80, GREEN);
	}

	EndDrawing();
}