#include <raylib.h>
#pragma once
class Entity
{
protected:
	Vector2 m_Scale;
	Vector2 m_Pos;
	float m_Rotation;
	float m_Speed;
public:
	// todo: have the type of body (use Box2D later)
	// todo: virtual void Update(float deltaTime); <- in the future
	virtual void Update();
	virtual void Move(float x, float y);
	virtual void Move(Vector2& newPos);
	virtual void SetPos(float x, float y);
	virtual void SetPos(Vector2& newPos);
	virtual Vector2 GetPos();
};

