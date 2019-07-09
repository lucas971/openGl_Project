#include "Cube.h"

Cube::Cube(Shader* shader) : GameObject(shader, verticesInCube)
{
	// Division de la taille

	float taille = .5f;

	// Vertices temporaires

	float verticesTmp[] = { -taille, -taille, -taille,   taille, -taille, -taille,   taille, taille, -taille,     // Face 1
						   -taille, -taille, -taille,   -taille, taille, -taille,   taille, taille, -taille,     // Face 1

						   taille, -taille, taille,   taille, -taille, -taille,   taille, taille, -taille,       // Face 2
						   taille, -taille, taille,   taille, taille, taille,   taille, taille, -taille,         // Face 2

						   -taille, -taille, taille,   taille, -taille, taille,   taille, -taille, -taille,      // Face 3
						   -taille, -taille, taille,   -taille, -taille, -taille,   taille, -taille, -taille,    // Face 3

						   -taille, -taille, taille,   taille, -taille, taille,   taille, taille, taille,        // Face 4
						   -taille, -taille, taille,   -taille, taille, taille,   taille, taille, taille,        // Face 4

						   -taille, -taille, -taille,   -taille, -taille, taille,   -taille, taille, taille,     // Face 5
						   -taille, -taille, -taille,   -taille, taille, -taille,   -taille, taille, taille,     // Face 5

						   -taille, taille, taille,   taille, taille, taille,   taille, taille, -taille,         // Face 6
						   -taille, taille, taille,   -taille, taille, -taille,   taille, taille, -taille };      // Face 6


	// Couleurs temporaires

	
	float colorX = (float)(rand() % 255) / 255.f;
	float colorY = (float)(rand() % 255) / 255.f;
	float colorZ = (float)(rand() % 255) / 255.f;

	float couleursTmp[] = {colorX, colorY, colorZ,   colorX, colorY, colorZ,  colorX, colorY, colorZ,           // Face 1
						   colorX, colorY, colorZ,   colorX, colorY, colorZ,  colorX, colorY, colorZ,           // Face 1
						   colorX, colorY, colorZ,	 colorX, colorY, colorZ,  colorX, colorY, colorZ,
						   colorX, colorY, colorZ,   colorX, colorY, colorZ,  colorX, colorY, colorZ,           // Face 2
						   colorX, colorY, colorZ,   colorX, colorY, colorZ,  colorX, colorY, colorZ,           // Face 2
						   colorX, colorY, colorZ,	 colorX, colorY, colorZ,  colorX, colorY, colorZ,
						   colorX, colorY, colorZ,   colorX, colorY, colorZ,  colorX, colorY, colorZ,           // Face 3
						   colorX, colorY, colorZ,   colorX, colorY, colorZ,  colorX, colorY, colorZ,           // Face 3
						   colorX, colorY, colorZ,	 colorX, colorY, colorZ,  colorX, colorY, colorZ,
						   colorX, colorY, colorZ,   colorX, colorY, colorZ,  colorX, colorY, colorZ,           // Face 4
						   colorX, colorY, colorZ,   colorX, colorY, colorZ,  colorX, colorY, colorZ,           // Face 4
						   colorX, colorY, colorZ,	 colorX, colorY, colorZ,  colorX, colorY, colorZ,
						   colorX, colorY, colorZ,   colorX, colorY, colorZ,  colorX, colorY, colorZ,           // Face 5
						   colorX, colorY, colorZ,   colorX, colorY, colorZ,  colorX, colorY, colorZ,           // Face 5
						   colorX, colorY, colorZ,	 colorX, colorY, colorZ,  colorX, colorY, colorZ,
						   colorX, colorY, colorZ,   colorX, colorY, colorZ,  colorX, colorY, colorZ,           // Face 6
						   colorX, colorY, colorZ,   colorX, colorY, colorZ,  colorX, colorY, colorZ};          // Face 6


	// Copie des valeurs dans les tableaux finaux

	for (int i(0); i < verticesCount; i++)
	{
		vertices[i] = verticesTmp[i];
		colors[i] = couleursTmp[i];
	}
}

Cube::~Cube()
{}

void Cube::print(glm::mat4& projection, glm::mat4& modelview)
{	

	// Activation du shader

	glUseProgram(shader->getProgramID());


	// Envoi des vertices

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, vertices);
	glEnableVertexAttribArray(0);


	// Envoi de la couleur

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, colors);
	glEnableVertexAttribArray(1);


	// Envoi des matrices

	glUniformMatrix4fv(glGetUniformLocation(shader->getProgramID(), "projection"), 1, GL_FALSE, value_ptr(projection));
	glUniformMatrix4fv(glGetUniformLocation(shader->getProgramID(), "modelview"), 1, GL_FALSE, value_ptr(modelview));


	// Rendu

	glDrawArrays(GL_TRIANGLES, 0, 36);


	// Désactivation des tableaux

	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(0);


	// Désactivation du shader

	glUseProgram(0);
}

GLfloat* Cube::getVertices()
{
	return vertices;
}

GLfloat* Cube::getColors()
{
	return colors;
}


