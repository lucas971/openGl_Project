#include "GameObject.h"

GameObject::GameObject(Shader* shader, int verticesCount) :
	shader(shader),
	verticesCount(verticesCount)
{
	vertices = (GLfloat*) malloc(verticesCount * sizeof(GLfloat));
	colors = (GLfloat*)malloc(verticesCount * sizeof(GLfloat));
}

GameObject::~GameObject()
{
}

void GameObject::print(glm::mat4& projection, glm::mat4& modelview)
{
}

void GameObject::translate(glm::vec3 translation)
{
	position += translation;
	for (int i = 0; i < verticesCount; i++) {
		if (i % 3 == 0) //x
			vertices[i] += translation.x;
		else if (i % 3 == 1) //y
			vertices[i] += translation.y;
		else
			vertices[i] += translation.z;
	}
}
