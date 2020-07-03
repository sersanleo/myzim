#include <GLAD/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "GameWindow.h"

int main(void) {
	GameWindow* myZimWindow = new GameWindow("MyZim", 1400, 800);
	myZimWindow->run();
	return 0;
}