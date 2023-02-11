#include "Player.h"
#include <raylib.h>
#include <box2d/b2_world.h>
#include <box2d/b2_polygon_shape.h>
#include <box2d/b2_fixture.h>
#include <iostream>

extern b2World* world;
extern float HEIGHT;
extern float WIDTH;

Player::Player(Vector2 size, Vector2 pos) : m_Pos({ 0, 0 }), m_Speed(3.0f), m_JumpVelocity(2.0f) {
	m_Size = size;

	// TODO: this should have an api for creating dynamic bodies
	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;

	// Middle of the screen
	bodyDef.position.Set(pos.x, pos.y);

	m_Body = world->CreateBody(&bodyDef);

	b2PolygonShape dynamicBox;
	dynamicBox.SetAsBox(m_Size.x, m_Size.y);

	b2FixtureDef fixtureDef;
	fixtureDef.shape = &dynamicBox;
	fixtureDef.density = 1.0f;
	fixtureDef.friction = 0.5f;
	fixtureDef.restitution = 0.1f;

	m_Body->CreateFixture(&fixtureDef);
}

void Player::Update() {
	b2Vec2 bodyPos = m_Body->GetPosition();

	m_Pos.x = bodyPos.x;
	m_Pos.y = -bodyPos.y;

	DrawRectangle(m_Pos.x, m_Pos.y, m_Size.x, m_Size.y, BLACK);

	if (IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT)) {
		m_Body->SetTransform({ bodyPos.x - m_Speed, bodyPos.y }, 0);
	}

	if (IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT)) {
		m_Body->SetTransform({ bodyPos.x + m_Speed, bodyPos.y }, 0);
	}

	if (IsKeyDown(KEY_SPACE)) {
		Jump();
	}
}

void Player::Jump() {
	b2Vec2 linearVelocity = m_Body->GetLinearVelocity();
	m_Body->SetLinearVelocity({ linearVelocity.x, linearVelocity.y + m_JumpVelocity });
}

Vector2 Player::GetPos() {
	return m_Pos;
}

Vector2 Player::GetMiddle() {
	return { m_Pos.x + (m_Size.x / 2), m_Pos.y + (m_Size.y / 2) };
}