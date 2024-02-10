#include <GL/glew.h>
#include <iostream>

#include "GLlog.h"

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
