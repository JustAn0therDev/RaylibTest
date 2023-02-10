#pragma once
#include "Entity.h"
#include <box2d/b2_body.h>

class Ground : public Entity
{
private:
	Vector2 m_Size;

public:
	virtual void Update() override;
	Ground(Vector2 m_Size, b2Body* body);
};

