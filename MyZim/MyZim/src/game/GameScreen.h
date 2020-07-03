#pragma once

#include "../engine/screen/Screen.h"
#include "world/World.h"

class GameScreen : public Screen {
private:
	World* world;
public:
	GameScreen(Window* window);

	void update(float delta);
	void render(float delta);

	void onScreenChanged() override;
	void onWindowSize(int width, int height) override;
	void onCursorPos(double oldX, double oldY, double newX, double newY) override;
	void onMouseButton(int button, int action, int mods, double x, double y) override;
	void onScroll(double xOffset, double yOffset) override;
	void onKey(int key, int scancode, int action, int mods) override;
};