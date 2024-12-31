#pragma once

#define GLCall(X) GLClearError(); X; GLLogCall(#X, __FILE__, __LINE__)

void GLClearError();
bool GLLogCall(const char* funcion, const char* file, int line);
