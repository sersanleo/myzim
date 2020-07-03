#include "Terrain.h"
#include <iostream>

const float Terrain::MIN_HEIGHT = -500.0f;
const float Terrain::MAX_HEIGHT = 500.0f;

Terrain::Terrain(World* world, int chunksWidth, int chunksHeight) {
	this->world = world;

	this->chunksWidth = chunksWidth;
	this->chunksHeight = chunksHeight;

	this->tilesWidth = chunksWidth * Chunk::SIZE;
	this->tilesHeight = chunksHeight * Chunk::SIZE;

	this->verticesWidth = chunksWidth * Chunk::RESOLUTION_TILES + 1;
	this->verticesHeight = chunksHeight * Chunk::RESOLUTION_TILES + 1;

	this->heightMap = new float[verticesWidth * verticesHeight] { 0 };

	for (int x = 0; x < chunksWidth; x++)
		for (int z = 0; z < chunksHeight; z++) {
			Chunk* chunk = new Chunk(this, x, z);
			addChunk(chunk);
		}
}

Terrain::~Terrain() {
	delete[] this->heightMap;

	std::cout << "Terrain destroyed!" << std::endl;
}

int Terrain::getChunkId(int x, int z) {
	return x + z * this->chunksWidth;
}

int Terrain::getChunkId(Chunk* chunk) {
	return getChunkId(chunk->x, chunk->z);
}

int Terrain::getVertexId(int x, int z) {
	return x + z * this->verticesWidth;
}

float Terrain::getVertexHeight(int x, int z) {
	return this->heightMap[getVertexId(x, z)];
}

glm::vec3 Terrain::getVertexNormal(int x, int z) {
	glm::vec3 normal = glm::vec3(0, 2 * Chunk::TILE_SIZE, 0);

	if (x == 0)
		normal.x = 2 * (getVertexHeight(x, z) - getVertexHeight(x + 1, z));
	else if (x == verticesWidth - 1)
		normal.x = 2 * (getVertexHeight(x - 1, z) - getVertexHeight(x, z));
	else
		normal.x = getVertexHeight(x - 1, z) - getVertexHeight(x + 1, z);

	if (z == 0)
		normal.z = 2 * (getVertexHeight(x, z) - getVertexHeight(x, z + 1));
	else if (z == verticesHeight - 1)
		normal.z = 2 * (getVertexHeight(x, z - 1) - getVertexHeight(x, z));
	else
		normal.z = getVertexHeight(x, z - 1) - getVertexHeight(x, z + 1);

	return glm::normalize(normal);
}

void Terrain::addChunk(Chunk* chunk) {
	this->chunks.insert({getChunkId(chunk) , chunk });
}

void Terrain::removeChunk(Chunk* chunk) {
	this->chunks.erase(getChunkId(chunk));
	delete chunk;
}

void Terrain::update(float delta) {
}

void Terrain::render(float delta) {
	for (const auto& chunk : chunks)
		chunk.second->render();
}
