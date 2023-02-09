#include "Player.h"
#include <raylib.h>

Player::Player() : m_Pos({ 0, 0 }), m_Speed(7.0f) {

}

void Player::Update() {
	DrawRectangle(m_Pos.x, m_Pos.y, 50, 50, WHITE);

	if (IsKeyDown(KEY_A)) {
		m_Pos.x -= m_Speed;
	}

	if (IsKeyDown(KEY_D)) {
		m_Pos.x += m_Speed;
	}
}

void Player::SetPos(float x, float y) {
	m_Pos.x = x;
	m_Pos.y = y;
}
