#pragma once

class InputEventHandler
{
public:
	virtual void onWindowSize(int width, int height) {}
	virtual void onCursorPos(double oldX, double oldY, double newX, double newY) {}
	virtual void onMouseButton(int button, int action, int mods, double x, double y) {}
	virtual void onScroll(double xOffset, double yOffset) {}
	virtual void onKey(int key, int scancode, int action, int mods) {}
};

