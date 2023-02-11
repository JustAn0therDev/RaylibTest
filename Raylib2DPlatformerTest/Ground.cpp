#include "Ground.h"
#include <raylib.h>
#include <iostream>

Ground::Ground(Vector2 size, b2Body* body) {
	m_Body = body;
	m_Size = size;
}

void Ground::Update() {
	DrawRectangle(m_Pos.x, m_Pos.y - m_Size.y, m_Size.x, m_Size.y, WHITE);

	b2Vec2 bodyPos = m_Body->GetPosition();

	m_Pos.x = bodyPos.x;
	m_Pos.y = -bodyPos.y;
}
