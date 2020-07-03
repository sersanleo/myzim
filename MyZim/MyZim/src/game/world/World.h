#pragma once

#include "../engine/screen/Screen.h"
#include "terrain/Terrain.h"
#include "camera/Camera.h"

class Terrain;
class Camera;

class World
{
private:
	Terrain* terrain;
	Camera* camera;
public:
	Screen* screen;

	World(Screen* screen);

	void update(float delta);
	void render(float delta);
};

