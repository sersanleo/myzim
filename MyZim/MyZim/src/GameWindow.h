#pragma once

#include "engine/window/Window.h"
#include "engine/screen/Screen.h"

class GameWindow : public Window {
private:
	void setCallbacks();

	void onWindowSize(int width, int height) override;
	void onCursorPos(double oldX, double oldY, double newX, double newY) override;
	void onMouseButton(int button, int action, int mods, double x, double y) override;
	void onScroll(double xOffset, double yOffset) override;
	void onKey(int key, int scancode, int action, int mods) override;
public:
	Screen* screen;

	GameWindow(std::string title, int width, int height);
	void run() override;
};