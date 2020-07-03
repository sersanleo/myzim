#include "GameScreen.h"
#include <iostream>

GameScreen::GameScreen(Window* window) : Screen(window) {
	this->world = new World(this);
}

void GameScreen::update(float delta) {
	world->update(delta);
}

void GameScreen::render(float delta) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	world->render(delta);
}

void GameScreen::onScreenChanged() {
	glClearDepth(1);
	glClearColor(0.678f, 0.867f, 1.0f, 1);

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
}

void GameScreen::onWindowSize(int width, int height) {
	glViewport(0, 0, width, height);
}

void GameScreen::onCursorPos(double oldX, double oldY, double newX, double newY) {
}

void GameScreen::onMouseButton(int button, int action, int mods, double x, double y) {

}

void GameScreen::onKey(int key, int scancode, int action, int mods) {
	if (key == GLFW_KEY_L) {
		glLineWidth(0.5f);
		glPolygonMode(GL_FRONT, GL_LINE);
	} else if (key == GLFW_KEY_T) {
		glPolygonMode(GL_FRONT, GL_FILL);
	}
}

void GameScreen::onScroll(double xOffset, double yOffset) {
}
