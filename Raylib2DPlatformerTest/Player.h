#include "Entity.h"

#pragma once
class Player : public Entity
{
public:
	Player();
	virtual void SetPos(float x, float y);
	virtual void Update();
	
private:
	Vector2 m_Pos;
	float m_Speed;
};

