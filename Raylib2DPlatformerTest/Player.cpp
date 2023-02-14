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
extern Camera2D camera;

Player::Player(Vector2 size, Vector2 pos, b2Body* body) : m_Pos({ 0, 0 }), m_Speed(1.0f), m_JumpVelocity(60.0f), m_FallVelocity(2.0f), m_IsGrounded(false) {
	m_Size = size;
	m_Body = body;
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

		Vector2 mousePos = { GetMouseX(), GetMouseY() };

		b2Vec2 currentLinearVelocity = m_Body->GetLinearVelocity();

		b2Vec2 direction = { (WIDTH / 2) - mousePos.x, ((HEIGHT / 2) + mousePos.y)};

		float cameraRelativeX = mousePos.x - camera.offset.x + m_Pos.x + 10.0f;
		float cameraRelativeY = mousePos.y - camera.offset.y + m_Pos.y + 25.0f;

		DrawCircle(cameraRelativeX, cameraRelativeY, 20, RED);

		float velocityY = 0;

		if (mousePos.y < (HEIGHT / 2)) {
			velocityY = direction.y * movementVelocity;
		}
		else {
			velocityY = direction.y * -movementVelocity;
		}

		m_Body->SetLinearVelocity({ direction.x * -movementVelocity, velocityY });
	}

	// TODO: for now, just check one collision because there's only one other game object in the world.
	b2ContactEdge* contactEdge = m_Body->GetContactList();

	//while (contactEdge != nullptr) {
	//	contactEdge->contact->GetFixtureA();
	//	
	//	contactEdge = contactEdge->next;
	//}

	if (contactEdge != nullptr) {
		m_IsGrounded = true;
		// TODO: Used dash
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