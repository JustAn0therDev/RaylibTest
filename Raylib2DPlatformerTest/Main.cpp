#include <iostream>
#include <string>
#include <raylib.h>
#include "rlgl.h"
#include "Scene.h"
#include "Player.h"
#include "Entity.h"
#include "box2d/b2_world.h"

const int WIDTH = 1280;
const int HEIGHT = 720;

int main() {
	InitWindow(WIDTH, HEIGHT, "3D walking? IDK");

	SetTargetFPS(60);

	b2Vec2 gravity(0, 9.8f);

	b2World* world = new b2World(gravity);

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

	delete world;

	CloseWindow();

	return EXIT_SUCCESS;
}