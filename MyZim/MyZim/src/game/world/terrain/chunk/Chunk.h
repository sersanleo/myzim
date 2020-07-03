#pragma once

#ifndef __CHUNK_H
#define __CHUNK_H

#include "../Terrain.h"
#include <iostream>
#include <GLAD/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

class Terrain;

class Chunk
{
private:
	Terrain* terrain;

	GLuint vao, buffers[2];
	glm::mat4 transformationMatrix;
public:
	static const unsigned int SIZE = 64, RESOLUTION_FACTOR = 2, RESOLUTION_TILES = SIZE * RESOLUTION_FACTOR,
		RESOLUTION_VERTICES = RESOLUTION_TILES + 1, VERTEX_COUNT = RESOLUTION_VERTICES * RESOLUTION_VERTICES,
		RENDERED_VERTICES = RESOLUTION_TILES * RESOLUTION_TILES * 2 * 3;

	static const float TILE_SIZE;

	const int x, z;
	const int tilesX, tilesZ;
	const int globalX, globalZ;
	bool dirty = true;

	Chunk(Terrain* terrain, int x, int z);
	~Chunk();

	float getVertexHeight(int x, int z);
	glm::vec3 getVertexNormal(int x, int z);

	void draftUpdate();
	void render();

	inline void print() {
		std::cout << "Chunk {x=" << this->x << ", z=" << this->z << "}" << std::endl;
	}
};

#endif