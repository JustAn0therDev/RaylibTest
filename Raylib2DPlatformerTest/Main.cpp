#include <iostream>
#include "raylib.h"

Camera3D globalCam{};

const int GLOBAL_CAM_DISTANCE_LIMIT = 25;
const int WIDTH = 1280;
const int HEIGHT = 720;
bool SHOULD_FOLLOW_THE_PLAYER_AFTER_ANIMATION = false;

struct entity {
	Vector3 pos;
	float speed;
} typedef Entity;

void Update(Entity& player) {
	BeginDrawing();

	globalCam.target = player.pos;

	BeginMode3D(globalCam);

	ClearBackground(RAYWHITE);

	DrawGrid(50, 10.0f);

	DrawCylinder(player.pos, 2.0f, 2.0f, 5.0f, 10, DARKBLUE);

	EndMode3D();

	if (globalCam.position.z <= -GLOBAL_CAM_DISTANCE_LIMIT &&
		globalCam.position.y >= GLOBAL_CAM_DISTANCE_LIMIT &&
		!SHOULD_FOLLOW_THE_PLAYER_AFTER_ANIMATION) {
		SHOULD_FOLLOW_THE_PLAYER_AFTER_ANIMATION = true;
	}

	if (globalCam.position.z > -GLOBAL_CAM_DISTANCE_LIMIT && !SHOULD_FOLLOW_THE_PLAYER_AFTER_ANIMATION) {
		globalCam.position.z -= 0.5f;
	}

	if (globalCam.position.y < GLOBAL_CAM_DISTANCE_LIMIT && !SHOULD_FOLLOW_THE_PLAYER_AFTER_ANIMATION) {
		globalCam.position.y += 0.5f;
	}

	//if ((int)globalCam.position.z == -GLOBAL_CAM_DISTANCE_LIMIT && (int)globalCam.position.y == GLOBAL_CAM_DISTANCE_LIMIT) {
	//	DrawText("NICE!", (WIDTH / 2) - 100, (HEIGHT / 2) - 40, 80, GREEN);
	//}

	// DrawText("NICE!", (WIDTH / 2) - 100, (HEIGHT / 2) - 40, 80, GREEN);

	EndDrawing();
}

int main() {
	InitWindow(WIDTH, HEIGHT, "Title");

	SetTargetFPS(60);

	globalCam.position = { 0, 0, 0 };
	globalCam.target = { 0, 0, 0 };
	globalCam.up = { 0, 2, 0 };
	globalCam.fovy = 90;
	globalCam.projection = CAMERA_PERSPECTIVE;

	Entity player;
	player.pos = { 0, 2.5f, 0 };
	player.speed = 2;

	while (!WindowShouldClose())
	{
		Update(player);

		if (IsKeyDown(KEY_R)) {
			globalCam.position.z = 0;
			globalCam.position.y = 0;
		}

		if (IsKeyDown(KEY_D)) {
			player.pos.x -= player.speed;
			globalCam.position.x -= player.speed;
		}
		
		if (IsKeyDown(KEY_A)) {
			player.pos.x += player.speed;
			globalCam.position.x += player.speed;
		}
		
		if (IsKeyDown(KEY_W)) {
			player.pos.z += player.speed;
			globalCam.position.z += player.speed;
		}
		
		if (IsKeyDown(KEY_S)) {
			player.pos.z -= player.speed;
			globalCam.position.z -= player.speed;
		}

		if (IsKeyDown(KEY_B)) {
			globalCam.up.y += 1;
		}

		std::cout << globalCam.up.y << std::endl;
	}

	CloseWindow();

	return EXIT_SUCCESS;
}