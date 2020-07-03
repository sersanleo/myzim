#pragma once

#include "../window/Window.h"
#include "../window/InputEventHandler.h"

class Screen : public InputEventHandler {
public:
	Window* window;

	Screen(Window* window) : window(window) { }
	virtual void update(float delta) = 0;
	virtual void render(float delta) = 0;

	virtual void onScreenChanged() { };
};

