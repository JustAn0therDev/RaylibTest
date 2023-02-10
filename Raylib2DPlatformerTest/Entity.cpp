#include "Entity.h"
#include <box2d/b2_body.h>

Entity::Entity() : m_Pos({ 0, 0 }), m_Speed(0), m_Rotation(0), m_Scale({ 1, 1 }), m_Body(nullptr) {

}

Entity::Entity(b2Body* body) : m_Pos({ 0, 0 }), m_Speed(0), m_Rotation(0), m_Scale({ 1, 1 }) {
	m_Body = body;
}

void Entity::Update() {
	b2Vec2 bodyPos = m_Body->GetPosition();

	m_Pos.x = bodyPos.x;
	m_Pos.y = -bodyPos.y;
}

void Entity::Move(float x, float y) {
	
}

void Entity::Move(Vector2& newPos) {

}

void Entity::SetPos(float x, float y) {

}

void Entity::SetPos(Vector2& newPos) {
}

Vector2 Entity::GetPos() {
	return { 0, 0 };
}
