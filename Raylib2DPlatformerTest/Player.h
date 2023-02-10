#include "Entity.h"
#include <box2d/b2_body.h>

#pragma once
class Player : public Entity
{
public:
	Player(Vector2 m_Size);
	virtual void SetPos(float x, float y) override;
	virtual void Update() override;
	
private:
	Vector2 m_Pos;
	float m_Speed;
	b2Body* m_Body;
	Vector2 m_Size;
};

