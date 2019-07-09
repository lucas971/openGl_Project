#pragma once

#include <glew.h>
#include <GLFW/glfw3.h>
#include <glm.hpp>
#include <gtx/transform.hpp>
#include <gtc/type_ptr.hpp>
#include "Cube.h"
#include "Chunk.h"
#include "controls.hpp"

#include <string>
#include <iostream>
#include <list>
#include <algorithm>
#include <functional>
class SceneOpenGL
{
	public:

		SceneOpenGL(std::string titreFenetre, int largeurFenetre, int hauteurFenetre);
		~SceneOpenGL();

		void addGameObject(GameObject* gameObject);
		void addChunk(Chunk* chunk);
		void removeChunk(Chunk* chunk);
		void removeGameObject(GameObject* gameObject);
		void mainLoop();
		bool init();

	private:
		void glConfig();
		std::list<GameObject*> gameObjectList;
		std::list<Chunk*> chunkList;
		std::string windowName;
		int windowWidth;
		int windowHeight;

		GLFWwindow* window;
};