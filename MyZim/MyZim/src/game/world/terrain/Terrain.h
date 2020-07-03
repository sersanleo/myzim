#pragma once

#ifndef __TERRAIN_H
#define __TERRAIN_H

#include <map>
#include "chunk/Chunk.h"
#include <glm/glm.hpp>
#include "../World.h"

class Chunk;
class World;

class Terrain
{
private:
	World* world;

	int chunksWidth, chunksHeight;
	int tilesWidth, tilesHeight;
	int verticesWidth, verticesHeight;

	float* heightMap;

	std::map<int, Chunk*> chunks;
public:
	static const float MIN_HEIGHT;
	static const float MAX_HEIGHT;

	Terrain(World* world, int chunksWidth, int chunksHeight);
	~Terrain();

	int getChunkId(int x, int z);
	int getChunkId(Chunk* chunk);
	int getVertexId(int x, int z);

	float getVertexHeight(int x, int z);
	glm::vec3 getVertexNormal(int x, int z);

	void addChunk(Chunk* chunk);
	void removeChunk(Chunk* chunk);

	void update(float delta);
	void render(float delta);
};

#endif