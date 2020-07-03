#include "Window.h"
#include <stdlib.h>
#include <iostream>

bool Window::glfwInitialized = false;

Window::Window(std::string title, int width, int height) {
	if (!glfwInitialized)
		initGlfw();

	this->title = title;
	this->width = width;
	this->height = height;

	window = glfwCreateWindow(width, height, title.c_str(), NULL, NULL);

	if (!window) {
		glfwTerminate();
		exit(0);
	}

	glfwMakeContextCurrent(window);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "Failed to initialize GLAD" << std::endl;
		exit(0);
	}

	glfwSetWindowUserPointer(window, this);
}

Window::~Window() {
	glfwDestroyWindow(window);
}

void Window::initGlfw() {
	if (glfwInit())
		glfwInitialized = true;
	else
		exit(0);
}

void Window::terminateGlfw() {
	if (glfwInitialized) {
		glfwTerminate();
		glfwInitialized = false;
	}
}

void Window::setWindowSizeCallback() {
	glfwSetWindowSizeCallback(window, [](GLFWwindow* window, int width, int height) {
		Window* _window = (Window*)glfwGetWindowUserPointer(window);
		_window->onWindowSize(width, height);
		_window->setWindowSize(width, height);
		});
}

void Window::setCursorPosCallback() {
	glfwSetCursorPosCallback(window, [](GLFWwindow* window, double x, double y) {
		Window* _window = (Window*)glfwGetWindowUserPointer(window);
		_window->onCursorPos(x, y, _window->getCursorX(), _window->getCursorY());
		_window->setCursorPos(x, y);
		});
}

void Window::setMouseButtonCallback() {
	glfwSetMouseButtonCallback(window, [](GLFWwindow* window, int button, int action, int mods) {
		Window* _window = (Window*)glfwGetWindowUserPointer(window);
		_window->onMouseButton(button, action, mods, _window->getCursorX(), _window->getCursorY());
		});
}

void Window::setScrollCallback() {
	glfwSetScrollCallback(window, [](GLFWwindow* window, double xOffset, double yOffset) {
		Window* _window = (Window*)glfwGetWindowUserPointer(window);
		_window->onScroll(xOffset, yOffset);
		});
}

void Window::setKeyCallback() {
	glfwSetKeyCallback(window, [](GLFWwindow* window, int key, int scancode, int action, int mods) {
		Window* _window = (Window*)glfwGetWindowUserPointer(window);
		_window->onKey(key, scancode, action, mods);
		});
}

void Window::setCursorPos(double x, double y) {
	this->cursorX = x;
	this->cursorY = y;
}

void Window::setWindowSize(int width, int height) {
	this->width = width;
	this->height = height;
}
