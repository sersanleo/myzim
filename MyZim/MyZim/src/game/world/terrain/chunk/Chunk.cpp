#include "Chunk.h"

#include <iostream>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>

const float Chunk::TILE_SIZE = 1.0f / RESOLUTION_FACTOR;

Chunk::Chunk(Terrain* terrain, int x, int z) :
	x(x),
	z(z),
	tilesX(x * Chunk::RESOLUTION_TILES),
	tilesZ(z * Chunk::RESOLUTION_TILES),
	globalX(x * Chunk::SIZE),
	globalZ(z * Chunk::SIZE) {
	this->terrain = terrain;

	transformationMatrix = glm::translate(glm::mat4(), glm::vec3(globalX, 0, globalZ));

	// Create VAO
	glGenVertexArrays(1, &vao);
	// Create buffers
	glGenBuffers(2, buffers);

	draftUpdate();
}

Chunk::~Chunk() {

}

float Chunk::getVertexHeight(int x, int z) {
	return terrain->getVertexHeight(tilesX + x, tilesZ + z);
}

glm::vec3 Chunk::getVertexNormal(int x, int z) {
	return terrain->getVertexNormal(tilesX + x, tilesZ + z);
}

void Chunk::draftUpdate() {
	glBindVertexArray(vao);

	// Vertices
	GLfloat arrayBuffer[Chunk::VERTEX_COUNT * 3 * 2];
	int pointer = 0;
	for (int x = 0; x < Chunk::RESOLUTION_VERTICES; x++)
		for (int z = 0; z < Chunk::RESOLUTION_VERTICES; z++) {
			arrayBuffer[pointer++] = x * Chunk::TILE_SIZE;
			arrayBuffer[pointer++] = x*z+getVertexHeight(x, z);
			arrayBuffer[pointer++] = z * Chunk::TILE_SIZE;

			glm::vec3 normal = getVertexNormal(x, z);
			arrayBuffer[pointer++] = normal.x;
			arrayBuffer[pointer++] = normal.y;
			arrayBuffer[pointer++] = normal.z;
		}

	glBindBuffer(GL_ARRAY_BUFFER, buffers[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(arrayBuffer), arrayBuffer, GL_DYNAMIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 3 * 2, (GLvoid*)0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 3 * 2, (GLvoid*)(sizeof(GLfloat) * 3));

	// Indices
	GLushort elementArrayBuffer[Chunk::RENDERED_VERTICES];
	pointer = 0;
	for (int x = 0; x < Chunk::RESOLUTION_TILES; x++)
		for (int z = 0; z < Chunk::RESOLUTION_TILES; z++) {
			GLushort v1, v2, v3, v4;

			if ((x + z) % 2 == 0) {
				v1 = x * Chunk::RESOLUTION_VERTICES + z;
				v2 = x * Chunk::RESOLUTION_VERTICES + z + 1;
				v3 = (x + 1) * Chunk::RESOLUTION_VERTICES + z;
				v4 = (x + 1) * Chunk::RESOLUTION_VERTICES + z + 1;
			} else {
				v1 = (x + 1) * Chunk::RESOLUTION_VERTICES + z;
				v2 = x * Chunk::RESOLUTION_VERTICES + z;
				v3 = (x + 1) * Chunk::RESOLUTION_VERTICES + z + 1;
				v4 = x * Chunk::RESOLUTION_VERTICES + z + 1;
			}

			elementArrayBuffer[pointer++] = v1;
			elementArrayBuffer[pointer++] = v2;
			elementArrayBuffer[pointer++] = v3;

			elementArrayBuffer[pointer++] = v3;
			elementArrayBuffer[pointer++] = v2;
			elementArrayBuffer[pointer++] = v4;
		}

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffers[1]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(elementArrayBuffer), elementArrayBuffer, GL_DYNAMIC_DRAW);
}

void Chunk::render() {
	glBindVertexArray(vao);

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);

	glDrawElements(GL_TRIANGLES, Chunk::RENDERED_VERTICES, GL_UNSIGNED_SHORT, 0);
}
