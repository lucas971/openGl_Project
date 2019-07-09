// Inclut les en-têtes standards
#include <stdio.h>
#include <stdlib.h>

#include "SceneOpenGL.h"
using namespace glm;

int main() {

	srand((int)time(NULL));

	//Création de scène
	SceneOpenGL scene("OpenCraft", 1920, 1080);
	if (!scene.init())
	{
		return -1;
	}

	//Chargement des shaders
	Shader* shader = new Shader("Shaders/couleur3D.vert", "Shaders/couleur3D.frag");
	shader->load();

	//Chargement des objects 3D
	Chunk* c1 = new Chunk(0, 0, shader);
	Chunk* c2 = new Chunk(-1, 0, shader);
	Chunk* c3 = new Chunk(0, -1, shader);
	Chunk* c4 = new Chunk(-1, -1, shader);
	scene.addChunk(c1);
	scene.addChunk(c2);
	scene.addChunk(c3);
	scene.addChunk(c4);
	scene.removeChunk(c4);

	//Boucle principale
	scene.mainLoop();
}