#pragma once

#include <iostream>
#include <string>
#include <fstream>
#include <string>

#include <glew.h>
#include <GLFW/glfw3.h>
class Shader
{
public:

	Shader();
	Shader(Shader const& shaderACopier);
	Shader(std::string vertexPath, std::string fragmentPath);
	~Shader();

	Shader& operator=(Shader const& shaderACopier);

	bool load();
	bool compileShader(GLuint& shader, GLenum type, std::string const& fichierSource);
	GLuint getProgramID() const;
	bool isLoaded();

private:
	
	bool loaded;
	GLuint vertexID;
	GLuint fragmentID;
	GLuint programID;

	std::string vertexSource;
	std::string fragmentSource;
};