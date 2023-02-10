#include "Entity.h"

#pragma once
class Player : public Entity
{
public:
	Player();
	virtual void SetPos(float x, float y) override;
	virtual void Update() override;
	
private:
	Vector2 m_Pos;
	float m_Speed;
};

