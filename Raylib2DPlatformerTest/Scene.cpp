#include "Scene.h"

Scene::Scene() {
	// TODO: for now, reserve space for only 50 entities.
	m_Entities.reserve(50);
}

Scene::~Scene() {
	for (Entity* entity : m_Entities) {
		delete entity;
	}
}

