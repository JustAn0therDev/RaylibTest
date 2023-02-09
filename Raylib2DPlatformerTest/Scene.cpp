#include "Scene.h"

Scene::~Scene() {
	for (Entity* entity : m_Entities) {
		delete entity;
	}
}

