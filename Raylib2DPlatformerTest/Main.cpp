#include <iostream>
#include <string>
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

void WriteDebugCameraInfo() {
	std::string positionInfo = "positionX: " +
		std::to_string(globalCam.position.x) +
		", positionY: " +
		std::to_string(globalCam.position.y) +
		", positionZ: " +
		std::to_string(globalCam.position.z);

	DrawText(positionInfo.c_str(), 2, 0, 20, DARKBROWN);

	std::string targetInfo = "targetX: " +
		std::to_string(globalCam.target.x) +
		", targetY: " +
		std::to_string(globalCam.target.y) +
		", targetZ: " +
		std::to_string(globalCam.target.z);

	DrawText(targetInfo.c_str(), 2, 20, 20, DARKBROWN);

	std::string upInfo = "upX: " +
		std::to_string(globalCam.up.x) +
		", upY: " +
		std::to_string(globalCam.up.y) +
		", upZ: " +
		std::to_string(globalCam.up.z);

	DrawText(upInfo.c_str(), 2, 40, 20, DARKBROWN);

	std::string fovYInfo = "Fov Y: " + std::to_string(globalCam.fovy);

	DrawText(fovYInfo.c_str(), 2, 60, 20, DARKBROWN);

	std::string projectionInfo = "Projection: " + std::to_string(globalCam.projection);

	DrawText(projectionInfo.c_str(), 2, 80, 20, DARKBROWN);
}

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

	WriteDebugCameraInfo();

	//if ((int)globalCam.position.z == -GLOBAL_CAM_DISTANCE_LIMIT && (int)globalCam.position.y == GLOBAL_CAM_DISTANCE_LIMIT) {
	//	DrawText("NICE!", (WIDTH / 2) - 100, (HEIGHT / 2) - 40, 80, GREEN);
	//}

	// DrawText("NICE!", (WIDTH / 2) - 100, (HEIGHT / 2) - 40, 80, GREEN);

	EndDrawing();
}

int main() {
	InitWindow(WIDTH, HEIGHT, "3D walking? IDK");

	SetTargetFPS(60);

	globalCam.position = { 0, 0, 0 };
	globalCam.target = { 0, 0, 0 };
	globalCam.up = { 0, 1, 0 };
	globalCam.fovy = 90;
	globalCam.projection = CAMERA_PERSPECTIVE;

	Entity player{};
	player.pos = { 0, 0, 0 };
	player.speed = 2;

	while (!WindowShouldClose())
	{
		Update(player);

		if (IsKeyDown(KEY_R) && SHOULD_FOLLOW_THE_PLAYER_AFTER_ANIMATION) {
			// RESET DATA
			globalCam.position.x = 0;
			globalCam.position.z = 0;
			globalCam.position.y = 0;
			player.pos.x = 0;
			player.pos.y = 0;
			player.pos.z = 0;
			globalCam.target = { 0, 0, 0 };
			SHOULD_FOLLOW_THE_PLAYER_AFTER_ANIMATION = false;
		}

		if (IsKeyDown(KEY_D) && SHOULD_FOLLOW_THE_PLAYER_AFTER_ANIMATION) {
			player.pos.x -= player.speed;
			globalCam.position.x -= player.speed;
		}
		
		if (IsKeyDown(KEY_A) && SHOULD_FOLLOW_THE_PLAYER_AFTER_ANIMATION) {
			player.pos.x += player.speed;
			globalCam.position.x += player.speed;
		}
		
		if (IsKeyDown(KEY_W) && SHOULD_FOLLOW_THE_PLAYER_AFTER_ANIMATION) {
			player.pos.z += player.speed;
			globalCam.position.z += player.speed;
		}
		
		if (IsKeyDown(KEY_S) && SHOULD_FOLLOW_THE_PLAYER_AFTER_ANIMATION) {
			player.pos.z -= player.speed;
			globalCam.position.z -= player.speed;
		}
	}

	CloseWindow();

	return EXIT_SUCCESS;
}