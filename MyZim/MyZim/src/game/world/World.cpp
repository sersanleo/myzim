#include "World.h"

World::World(Screen* screen) {
	this->screen = screen;

	this->terrain = new Terrain(this, 2, 2);

	this->camera = new Camera(this, 0, 0, 0, glm::radians(-90.f), 0);
}

void World::update(float delta) {
	terrain->update(delta);
}

void World::render(float delta) {
	terrain->render(delta);
}