#include <iostream>
#include <string>
#include <raylib.h>
#include "rlgl.h"
#include "Scene.h"
#include "Player.h"
#include "Entity.h"
#include <box2d/b2_world.h>
#include <box2d/b2_body.h>
#include <box2d/b2_polygon_shape.h>
#include <box2d/b2_fixture.h>
#include "Physics.h"
#include "Ground.h"

float WIDTH = 1280.0f;
float HEIGHT = 720.0f;
b2World* world = nullptr;
Camera2D camera{};
const int TARGET_FPS = 60;

int main() {
	InitWindow(WIDTH, HEIGHT, "Smash beat'em up");

	SetTargetFPS(TARGET_FPS);

	b2Vec2 gravity(0, -9.8f);

	world = new b2World(gravity);

	float timeStep = 1.0f / TARGET_FPS;

	uint32_t velocityIterations = 6;
	uint32_t positionIterations = 2;

	Vector2 groundSize = { WIDTH, HEIGHT / 2 };

	Vector2 groundPos = { 0, -HEIGHT };

	b2Body* groundBody = Physics::CreateGround(groundSize, groundPos);

	Ground* ground = new Ground(groundSize, groundBody);

	Vector2 playerSize = { 20, 40 };

	Vector2 playerPos = { (WIDTH / 2) - playerSize.x / 2, -(HEIGHT / 2) + (playerSize.y * 2) };

	Player* player = new Player(playerSize, playerPos);

	camera.offset = { WIDTH / 2, HEIGHT / 2 };
	camera.rotation = 0;
	camera.zoom = 1;

	Scene mainScene;
	mainScene.m_Entities.emplace_back(player);
	mainScene.m_Entities.emplace_back(ground);

	while (!WindowShouldClose())
	{
		BeginDrawing();

		BeginMode2D(camera);

		camera.target = player->GetMiddle();

		world->Step(timeStep, velocityIterations, positionIterations);

		ClearBackground(SKYBLUE);

		for (Entity* entity : mainScene.m_Entities) {
			entity->Update();
		}

		if (IsKeyDown(KEY_ESCAPE)) {
			break;
		}

		if (IsKeyDown(KEY_Z) && camera.zoom < 5) {
			camera.zoom += 1;
		}

		if (IsKeyDown(KEY_X) && camera.zoom > 1) {
			camera.zoom -= 1;
		}

		EndMode2D();

		EndDrawing();
	}

	delete world;

	CloseWindow();

	return EXIT_SUCCESS;
}