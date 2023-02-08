#include <iostream>
#include <string>
#include "raylib.h"
#include "rlgl.h"
#include "Scene.h"
#include "Player.h"
#include "Entity.h"

Camera3D globalCam{};

const int WIDTH = 1280;
const int HEIGHT = 720;

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

int main() {
	InitWindow(WIDTH, HEIGHT, "3D walking? IDK");

	SetTargetFPS(60);

	globalCam.position = { 0, 0, 0 };
	// globalCam.target = player.pos;
	globalCam.up = { 0, 1, 0 };
	globalCam.fovy = 90;
	globalCam.projection = CAMERA_PERSPECTIVE;

	Player player;

	Scene* scene = new Scene;
	scene->m_Entities.emplace_back(player);

	while (!WindowShouldClose())
	{
		for (Entity& entity : scene->m_Entities) {
			entity.Update();
		}

		if (IsKeyDown(KEY_ESCAPE)) {
			break;
		}
	}

	CloseWindow();

	return EXIT_SUCCESS;
}