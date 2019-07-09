#pragma once
// Includes OpenGL
#include <glew.h>

// Includes GLM
#include <glm.hpp>
#include <gtx/transform.hpp>
#include <gtc/type_ptr.hpp>

// Includes Shader
#include "Shader.h"

class GameObject {
public :
	GameObject(Shader* shader, int numberOfVertices);
	~GameObject();
	virtual void print(glm::mat4& projection, glm::mat4& modelview);
	void translate(glm::vec3 translation);
protected :
	int verticesCount;
	Shader* shader;
	GLfloat* vertices;
	GLfloat* colors;
	glm::vec3 position;
};