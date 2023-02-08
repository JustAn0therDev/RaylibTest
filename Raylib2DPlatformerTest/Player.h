#include "Entity.h"

#pragma once
class Player : public Entity
{
public:
	Vector2 m_Pos;
	float m_Speed;

	void Move(float x, float y);
	void Move(Vector2& newPos);
	void SetPos(float x, float y);
	void SetPos(Vector2& newPos);
	Vector2 GetPos();
};

