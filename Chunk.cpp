#include "Chunk.h"

Chunk::Chunk(int xChunk, int yChunk, Shader* shader) : shader(shader), cubeArray()
{
	ChunkPosition = glm::vec2(xChunk, yChunk);
	BottomLeftWorldPosition = glm::vec2(xChunk * chunkWidth, yChunk * chunkWidth);
	
	for (int x = 0; x < chunkWidth; x++) {
		for (int y = 0; y < chunkWidth; y++) {
			for (int z = 0; z < chunkHeigth; z++) {
				Cube* c = new Cube(shader);
				cubeArray[x][y][z] = c;
				cubeArray[x][y][z]->translate(glm::vec3(xChunk * chunkWidth + x, yChunk * chunkWidth + y, -z));

				GLfloat* ver(c->getVertices());
				for (int i = 0; i < verticesInCube; i++) {
					GLfloat v = ver[i];
					vertices.push_back(v);
				}
				GLfloat* col(c->getColors());
				for (int i = 0; i < verticesInCube; i++) {
					GLfloat v = col[i];
					colors.push_back(v);
				}
			}
		}
	}
}

Chunk::~Chunk()
{
}

void Chunk::print(glm::mat4& projection, glm::mat4& modelview)
{
	// Activation du shader

	glUseProgram(shader->getProgramID());


	// Envoi des vertices

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, &vertices[0]);
	glEnableVertexAttribArray(0);


	// Envoi de la couleur

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, &colors[0]);
	glEnableVertexAttribArray(1);


	// Envoi des matrices

	glUniformMatrix4fv(glGetUniformLocation(shader->getProgramID(), "projection"), 1, GL_FALSE, value_ptr(projection));
	glUniformMatrix4fv(glGetUniformLocation(shader->getProgramID(), "modelview"), 1, GL_FALSE, value_ptr(modelview));


	// Rendu
	glDrawArrays(GL_TRIANGLES, 0, 36 * chunkWidth * chunkWidth * chunkHeigth);


	// Désactivation des tableaux

	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(0);


	// Désactivation du shader

	glUseProgram(0);
}


