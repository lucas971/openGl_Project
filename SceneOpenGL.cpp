#include "SceneOpenGL.h"

using namespace glm;
SceneOpenGL::SceneOpenGL(std::string windowName, int windowWidth, int windowHeight) : 
	windowName(windowName), 
	windowWidth(windowWidth),
	windowHeight(windowHeight), 
	window(0)
{}

SceneOpenGL::~SceneOpenGL()
{}

bool SceneOpenGL::init()
{
	// Initialise GLFW
	if (!glfwInit())
	{
		std::cout << "Failed to initialize GLFW\n" << std::endl;
		return false;
	}


	//Crée la fenêtre
	glfwWindowHint(GLFW_SAMPLES, 4); // 4x antialiasing
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); 
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1); 
	//glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // On ne veut pas l'ancien OpenGL

	// Ouvre une fenêtre et crée son contexte OpenGl
	window = glfwCreateWindow(windowWidth, windowHeight, "OpenGL_Challenge", NULL, NULL);
	if (window == NULL) {
		std::cout << "Failed to open GLFW window. If you have an Intel GPU, they are not 3.3 compatible. Try the 2.1 version of the tutorials.\n" << std::endl;
		glfwTerminate();
		return false;
	}
	glfwMakeContextCurrent(window); // Build the window

	//Initialise Glew
	glewExperimental = true; 
	if (glewInit() != GLEW_OK) {
		std::cout << "Failed to initialize GLEW\n" << std::endl;
		return false;
	}

	glConfig();
	return true;
}

void SceneOpenGL::glConfig()
{
	// Activation des textures
	glEnable(GL_TEXTURE_2D);
	// Enable depth test
	glEnable(GL_DEPTH_TEST);
	// Accept fragment if it closer to the camera than the former one
	glDepthFunc(GL_LESS);
	// Cull triangles which normal is not towards the camera
	glDisable(GL_CULL_FACE);
	// Assure que l'on peut capturer la touche d'échappement enfoncée ci-dessous
	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
	// Hide the mouse and ensure mouse mouvements input
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	// Sets the background color to dark blue
	glClearColor(0.0f, 0.0f, 0.4f, 0.0f);
}

void SceneOpenGL::addGameObject(GameObject* gameObject)
{
	gameObjectList.push_back(gameObject);
}

void SceneOpenGL::addChunk(Chunk* chunk)
{
	chunkList.push_back(chunk);
}

void SceneOpenGL::removeChunk(Chunk* chunk)
{
	chunkList.remove(chunk);
}

void SceneOpenGL::removeGameObject(GameObject* gameObject)
{
	gameObjectList.remove(gameObject);
}

void SceneOpenGL::mainLoop()
{
	bool terminer(false);
	// Matrices

	mat4 projection;
	mat4 model;
	mat4 view;
	mat4 modelview;

	Shader* shader = new Shader("Shaders/couleur3D.vert", "Shaders/couleur3D.frag");
	shader->load();

	Chunk* c1 = new Chunk(0, 0, shader);


	// Boucle principale
	do
	{
		// Nettoyage de l'écran
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		computeMatricesFromInputs(window, windowWidth, windowHeight);

		//Mise à jour de la ModelView
		model = mat4(1.0);
		modelview = model * getViewMatrix();
		projection = getProjectionMatrix();


		//Affichage des objets 3D
		for (GameObject* object : gameObjectList) {
			object->print(projection, modelview);
		}

		for (Chunk* chunk : chunkList) {
			chunk->print(projection, modelview);
		}

		// Actualisation de la fenêtre
		glfwSwapBuffers(window);
		glfwPollEvents();

	} while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS &&
		glfwWindowShouldClose(window) == 0);
}
