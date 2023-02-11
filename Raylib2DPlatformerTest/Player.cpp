#include "Player.h"
#include <raylib.h>
#include <box2d/b2_world.h>
#include <box2d/b2_polygon_shape.h>
#include <box2d/b2_fixture.h>
#include <box2d/b2_contact.h>
#include <iostream>

extern b2World* world;
extern float HEIGHT;
extern float WIDTH;

Player::Player(Vector2 size, Vector2 pos) : m_Pos({ 0, 0 }), m_Speed(1.0f), m_JumpVelocity(60.0f), m_FallVelocity(2.0f), m_IsGrounded(false) {
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
	// fixtureDef.restitution = 0.1f;

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

	if (IsKeyDown(KEY_S)) {
		m_Body->SetLinearVelocity({ m_Body->GetLinearVelocity().x, m_Body->GetLinearVelocity().y - 1000 });
	}

	if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
		float movementVelocity = m_JumpVelocity * 5;

		Vector2 mousePos = GetMousePosition();

		b2Vec2 currentLinearVelocity = m_Body->GetLinearVelocity();

		b2Vec2 direction = { (WIDTH / 2) - mousePos.x, ((HEIGHT / 2) + mousePos.y)};

		DrawLine(GetMiddle().x, GetMiddle().y, mousePos.x, mousePos.y, RED);

		float velocityY = 0;

		if (mousePos.y < (HEIGHT / 2)) {
			velocityY = direction.y * movementVelocity;
		}
		else {
			velocityY = direction.y * -movementVelocity;
		}

		m_Body->SetLinearVelocity({ direction.x * -movementVelocity, velocityY });
	}

	b2ContactEdge* contactEdge = m_Body->GetContactList();

	//while (contactEdge != nullptr) {
	//	contactEdge->contact->GetFixtureA();

	//	// TODO: for now, just check one collision because there's only one other object in the world.
	//	contactEdge = contactEdge->next;
	//}

	if (contactEdge != nullptr) {
		m_IsGrounded = true;
	}
	else {
		m_IsGrounded = false;
	}

	if (IsKeyDown(KEY_SPACE) && m_IsGrounded) {
		Jump();
	}

	if (!m_IsGrounded) {
		m_Body->SetLinearVelocity({ m_Body->GetLinearVelocity().x, m_Body->GetLinearVelocity().y - m_FallVelocity });
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