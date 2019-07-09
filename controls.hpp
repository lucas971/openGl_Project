#pragma once

#include <GLFW/glfw3.h>
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>


void computeMatricesFromInputs(GLFWwindow* window, int windowWidth, int windowHeight);
glm::mat4 getViewMatrix();
glm::mat4 getProjectionMatrix();