#include <iostream>
#include <string>
#include "raylib.h"
#include "rlgl.h"
#include "Scene.h"
#include "Player.h"
#include "Entity.h"

const int WIDTH = 1280;
const int HEIGHT = 720;

int main() {
	InitWindow(WIDTH, HEIGHT, "3D walking? IDK");

	SetTargetFPS(60);

	Player* player = new Player;

	player->SetPos((WIDTH / 2) - 25, (HEIGHT / 2) - 25);

	Scene mainScene;
	mainScene.m_Entities.emplace_back(player);

	while (!WindowShouldClose())
	{
		BeginDrawing();

		ClearBackground(BLACK);

		for (Entity* entity : mainScene.m_Entities) {
			entity->Update();
		}

		if (IsKeyDown(KEY_ESCAPE)) {
			break;
		}

		EndDrawing();
	}

	CloseWindow();

	return EXIT_SUCCESS;
}