#pragma once
#include <glm.hpp>
#include <vector>

#include <glew.h>

#include "Shader.h"
#include "GameObject.h"
#include "Cube.h"

const int chunkWidth = 16;
const int chunkHeigth = 256;

class Chunk {
public:
	Chunk(int xChunk, int yChunk, Shader* shader);
	~Chunk();
	Cube* cubeArray[chunkWidth][chunkWidth][chunkHeigth];
	void print(glm::mat4& projection, glm::mat4& modelview);
private:
	Shader* shader;
	glm::vec2 ChunkPosition;
	glm::vec2 BottomLeftWorldPosition;
	std::vector<GLfloat> vertices;
	std::vector<GLfloat> colors;
};