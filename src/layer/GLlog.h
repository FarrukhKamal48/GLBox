#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#define GLCall(X) GLClearError(); X; GLLogCall(#X, __FILE__, __LINE__)

void GLClearError();
bool GLLogCall(const char* funcion, const char* file, int line);
