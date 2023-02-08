#include <raylib.h>
#pragma once
class Entity
{
private:
	Vector2 m_Pos;
public:
	float m_Speed;
	// todo: check the type of body (might as well use the b2world thingy, i forgor the name of the lib)

	// todo: does my update function need a deltaTime or something? 
	// I know its just a test project, but would be nice to get it from the OS and pass it here.
	// void Update(float deltaTime) -> in the future
	virtual void Update() = 0;
};

