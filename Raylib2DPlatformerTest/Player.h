#include "Entity.h"
#include <box2d/b2_body.h>

#pragma once
class Player : public Entity
{
public:
	Player(Vector2 size, Vector2 pos);
	virtual void SetPos(float x, float y) override;
	virtual void Update() override;
	virtual Vector2 GetPos() override;
	Vector2 GetMiddle();
	
private:
	Vector2 m_Pos;
	float m_Speed;
	b2Body* m_Body;
	Vector2 m_Size;

	void Jump();
};

