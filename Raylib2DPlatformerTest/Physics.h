#pragma once
#include <box2d/b2_body.h>
#include <raylib.h>

class Physics
{
public:
	static b2Body* CreateStaticBody(Vector2 size, Vector2 pos);
	static b2Body* CreateDynamicBody(Vector2 size, Vector2 pos);
};

