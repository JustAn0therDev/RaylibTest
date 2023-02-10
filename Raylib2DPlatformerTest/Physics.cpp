#include "Physics.h"
#include <box2d/b2_world.h>
#include <box2d/b2_polygon_shape.h>
#include <box2d/b2_body.h>
#include <raylib.h>

extern b2World* world;
extern float HEIGHT;
extern float WIDTH;

// TODO: this function should receive information like size, position etc.
b2Body* Physics::CreateGround(Vector2 size, Vector2 pos) {
	b2BodyDef groundBodyDef;
	groundBodyDef.position.Set(pos.x, pos.y);

	b2Body* groundBody = world->CreateBody(&groundBodyDef);

	b2PolygonShape groundBox;
	groundBox.SetAsBox(size.x, size.y);

	groundBody->CreateFixture(&groundBox, 0.0f);
	
	return groundBody;
}
