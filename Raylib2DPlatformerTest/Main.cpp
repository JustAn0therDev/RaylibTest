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

int main() {
	InitWindow(WIDTH, HEIGHT, "3D walking? IDK");

	SetTargetFPS(60);

	b2Vec2 gravity(0, -9.8f);

	world = new b2World(gravity);

	float timeStep = 1.0f / 60.0f;

	uint32_t velocityIterations = 6;
	uint32_t positionIterations = 2;

	Vector2 groundSize = { WIDTH, 40.0f };

	Vector2 groundPos = { 0, -(HEIGHT - (groundSize.y / 2)) };

	b2Body* groundBody = Physics::CreateGround(groundSize, groundPos);

	Ground* ground = new Ground(groundSize, groundBody);

	Entity* player = new Player({ 50, 50 });

	Scene mainScene;
	mainScene.m_Entities.emplace_back(player);
	mainScene.m_Entities.emplace_back(ground);

	while (!WindowShouldClose())
	{
		BeginDrawing();

		// calling Step() will make the world "move" by one frame.
		world->Step(timeStep, velocityIterations, positionIterations);

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