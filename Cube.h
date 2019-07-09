#pragma once

#include "GameObject.h"
#include <time.h> 
// Classe Cube

const int verticesInCube = 108;

enum CubeType { 
	Dirt,
	Stone,
	Gravel,
	BedRock
	};
class Cube : public GameObject
{
public:
	Cube(Shader* shader);
	~Cube();
	int id = 1;
	void print(glm::mat4& projection, glm::mat4& modelview) override;
	GLfloat* getVertices();
	GLfloat* getColors();
private:

};
