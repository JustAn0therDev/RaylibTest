#include "Player.h"
#include <raylib.h>

void Player::Update() {
}

void Player::Move(float x, float y) {
	m_Pos.x += x;
	m_Pos.y += y;
}

void Player::Move(Vector2& newPos) {
	m_Pos.x += newPos.x;
	m_Pos.y += newPos.y;
}

void Player::SetPos(float x, float y) {
	m_Pos.x = x;
	m_Pos.y = y;
}

void Player::SetPos(Vector2& newPos) {
	m_Pos = newPos;
}

Vector2 Player::GetPos() {
	return m_Pos;
}
