#pragma once

#include <string>
#include <GLAD/glad.h>
#include <GLFW/glfw3.h>
#include "InputEventHandler.h"

class Window : protected InputEventHandler {
private:
	static bool glfwInitialized;

	static void initGlfw();
	static void terminateGlfw();
protected:
	std::string title;
	int width, height;
	double cursorX, cursorY;

	// Callbacks
	void setWindowSizeCallback();
	void setCursorPosCallback();
	void setMouseButtonCallback();
	void setScrollCallback();
	void setKeyCallback();
public:
	GLFWwindow* window;

	Window(std::string title, int width, int height);
	~Window();

	virtual void run() = 0;
	inline std::string getTitle() {
		return title;
	}
	inline int getWidth() {
		return width;
	}
	inline int getHeight() {
		return height;
	}
	inline double getCursorX() {
		return cursorX;
	}
	inline double getCursorY() {
		return cursorY;
	}

	void setCursorPos(double x, double y);
	void setWindowSize(int width, int height);
};

