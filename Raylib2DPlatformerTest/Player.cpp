#include "Player.h"
#include <raylib.h>
#include <box2d/b2_world.h>
#include <box2d/b2_polygon_shape.h>
#include <box2d/b2_fixture.h>
#include <iostream>

extern b2World* world;
extern float HEIGHT;
extern float WIDTH;

Player::Player(Vector2 size) : m_Pos({ 0, 0 }), m_Speed(7.0f) {
	m_Size = size;

	// TODO: this should have an api for creating dynamic bodies
	b2BodyDef bodyDef;
	bodyDef.type = b2_kinematicBody;

	// Middle of the screen
	bodyDef.position.Set((WIDTH / 2) - m_Size.x / 2, -(HEIGHT / 2) + m_Size.y / 2);

	m_Body = world->CreateBody(&bodyDef);

	b2PolygonShape dynamicBox;
	dynamicBox.SetAsBox(m_Size.x, m_Size.y);

	b2FixtureDef fixtureDef;
	fixtureDef.shape = &dynamicBox;
	fixtureDef.density = 1.0f;
	fixtureDef.friction = 0.3f;
	fixtureDef.restitution = 0.2f;

	m_Body->CreateFixture(&fixtureDef);
}

void Player::Update() {
	b2Vec2 bodyPos = m_Body->GetPosition();

	m_Pos.x = bodyPos.x;
	m_Pos.y = -bodyPos.y;

	DrawRectangle(m_Pos.x, m_Pos.y, 50, 50, WHITE);

	if (IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT)) {
		m_Body->SetTransform({ bodyPos.x - m_Speed, bodyPos.y }, 0);
	}

	if (IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT)) {
		m_Body->SetTransform({ bodyPos.x + m_Speed, bodyPos.y }, 0);
	}
}

void Player::SetPos(float x, float y) {
	m_Pos.x = x;
	m_Pos.y = y;
}
