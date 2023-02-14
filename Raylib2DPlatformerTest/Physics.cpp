#include "Physics.h"
#include <box2d/b2_world.h>
#include <box2d/b2_polygon_shape.h>
#include <box2d/b2_body.h>
#include <box2d/b2_fixture.h>
#include <raylib.h>

extern b2World* world;
extern float HEIGHT;
extern float WIDTH;

b2Body* Physics::CreateStaticBody(Vector2 size, Vector2 pos) {
	b2BodyDef groundBodyDef;
	groundBodyDef.position.Set(pos.x, pos.y);

	b2Body* groundBody = world->CreateBody(&groundBodyDef);

	b2PolygonShape groundBox;
	groundBox.SetAsBox(size.x, size.y);

	groundBody->CreateFixture(&groundBox, 0.0f);
	
	return groundBody;
}

b2Body* Physics::CreateDynamicBody(Vector2 size, Vector2 pos) {
	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;

	bodyDef.position.Set(pos.x, pos.y);

	b2Body* body = world->CreateBody(&bodyDef);

	b2PolygonShape dynamicBox;
	dynamicBox.SetAsBox(size.x, size.y);

	b2FixtureDef fixtureDef;
	fixtureDef.shape = &dynamicBox;
	fixtureDef.density = 1.0f;
	fixtureDef.friction = 0.5f;
	fixtureDef.restitution = 0.1f;

	body->CreateFixture(&fixtureDef);

	return body;
}
