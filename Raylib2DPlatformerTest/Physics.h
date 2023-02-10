#pragma once
#include <box2d/b2_body.h>
#include <raylib.h>

static class Physics
{
public:
	static b2Body* CreateGround(Vector2 size, Vector2 pos);
};

