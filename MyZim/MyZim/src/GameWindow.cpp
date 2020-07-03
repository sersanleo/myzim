#include "GameWindow.h"
#include "game/GameScreen.h"
#include "game/world/terrain/Terrain.h"
#include <iostream>
#include <chrono>
#include <algorithm>

GameWindow::GameWindow(std::string title, int width, int height) : Window(title, width, height) {

}

void GameWindow::run() {
	screen = new GameScreen(this);

	screen->onScreenChanged();
	screen->onWindowSize(width, height);

	setCallbacks();

	std::chrono::high_resolution_clock::time_point t1 = std::chrono::high_resolution_clock::now();
	std::chrono::high_resolution_clock::time_point t2;
	float delta;

	while (!glfwWindowShouldClose(window)) {
		t2 = std::chrono::high_resolution_clock::now();
		delta = std::min(std::chrono::duration_cast<std::chrono::duration<float>>(t2 - t1).count(), 0.1f);
		t1 = t2;

		this->screen->update(delta);
		this->screen->render(delta);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();
}

void GameWindow::setCallbacks() {
	this->setWindowSizeCallback();
	this->setCursorPosCallback();
	this->setMouseButtonCallback();
	this->setScrollCallback();
	this->setKeyCallback();
}

void GameWindow::onWindowSize(int width, int height) {
	this->screen->onWindowSize(width, height);
}

void GameWindow::onCursorPos(double oldX, double oldY, double newX, double newY) {
	this->screen->onCursorPos(oldX, oldY, newX, newY);
}

void GameWindow::onMouseButton(int button, int action, int mods, double x, double y) {
	this->screen->onMouseButton(button, action, mods, x, y);
}

void GameWindow::onScroll(double xOffset, double yOffset) {
	this->screen->onScroll(xOffset, yOffset);
}

void GameWindow::onKey(int key, int scancode, int action, int mods) {
	this->screen->onKey(key, scancode, action, mods);
}