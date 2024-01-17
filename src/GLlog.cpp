#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>

#define GLCall(X) GLClearError(); X; GLLogCall(#X, __FILE__, __LINE__)

void GLClearError() {
    while (glGetError() != GL_NO_ERROR);
}

bool GLLogCall(const char* funcion, const char* file, int line) {
    while (GLenum error = glGetError()) {
        std::cout << "[GL Error] (" << error << "): " 
            << funcion << ", line " << line << " in " << file << std::endl;
        return false;
    }
    return true;
}
